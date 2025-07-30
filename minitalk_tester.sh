#!/bin/bash

# ==============================================================================
# |                     SCRIPT DE TEST ROBUSTE POUR MINITALK                     |
# |                          Rédigé par un expert Gemini                         |
# ==============================================================================
#
#   Objectif: Automatiser les tests de fiabilité, de robustesse et de conformité
#             du projet minitalk (client et serveur).
#
#   Usage:
#       ./run_tests.sh          - Exécuter tous les tests.
#       ./run_tests.sh [n]...   - Exécuter des tests spécifiques par numéro.
#                                 (ex: ./run_tests.sh 1 5 10)
#

# --- Configuration Globale ---
CLIENT_SRC="client.c"
SERVER_SRC="server.c"
CLIENT_BIN="client"
SERVER_BIN="server"
SERVER_LOG="server_output.log"
VALGRIND_LOG="valgrind_output.log"
TIMEOUT_DURATION="15s" # Timeout pour les opérations potentiellement bloquantes

# --- Codes de Couleur ---
C_RESET='\033[0m'
C_RED='\033[0;31m'
C_GREEN='\033[0;32m'
C_YELLOW='\033[0;33m'
C_BLUE='\033[0;34m'
C_CYAN='\033[0;36m'

# --- Compteurs de tests ---
tests_passed=0
tests_failed=0
server_pid=0
valgrind_installed=false

# --- Fonctions Utilitaires ---

# Affiche un en-tête pour un test
print_header() {
    echo -e "\n${C_BLUE}======================================================================${C_RESET}"
    echo -e "${C_CYAN}>>> TEST $1: $2${C_RESET}"
    echo -e "${C_BLUE}======================================================================${C_RESET}"
}

# Affiche un message de succès
print_success() {
    echo -e "${C_GREEN}[✔ SUCCÈS]${C_RESET} $1"
    ((tests_passed++))
}

# Affiche un message d'échec avec une suggestion
print_failure() {
    echo -e "${C_RED}[✖ ÉCHEC]${C_RESET} $1"
    if [ -n "$2" ]; then
        echo -e "${C_YELLOW}[PISTE] → ${C_RESET}$2"
    fi
    ((tests_failed++))
}

# Nettoie les processus et les fichiers journaux après un test
cleanup_after_test() {
    if [ $server_pid -ne 0 ] && ps -p $server_pid > /dev/null; then
        kill -9 $server_pid >/dev/null 2>&1
        wait $server_pid 2>/dev/null
    fi
    server_pid=0
    rm -f $SERVER_LOG $VALGRIND_LOG
}

# Nettoie tout, y compris les binaires (pour le début et la fin du script)
full_cleanup() {
    cleanup_after_test
    rm -f $CLIENT_BIN $SERVER_BIN
}

# Intercepte le signal de sortie (CTRL+C) pour un nettoyage complet
trap full_cleanup EXIT

# Vérifie l'existence des fichiers sources
check_sources() {
    if [ ! -f "$CLIENT_SRC" ] || [ ! -f "$SERVER_SRC" ]; then
        print_failure "Fichiers sources ($CLIENT_SRC, $SERVER_SRC) introuvables." "Assurez-vous que le script est dans le même répertoire que vos sources."
        exit 1
    fi
}

# Compile le client et le serveur
compile_programs() {
    echo -e "${C_YELLOW}--- Compilation des programmes ---${C_RESET}"
    # Utilise 'make re' pour s'assurer que tout est propre et recompilé
    make_output=$(make re 2>&1)
    if [ $? -ne 0 ] || [ ! -f "$CLIENT_BIN" ] || [ ! -f "$SERVER_BIN" ]; then
        print_failure "La compilation a échoué." "Vérifiez les erreurs de compilation ci-dessous."
        echo -e "$make_output"
        exit 1
    fi
    echo -e "${C_GREEN}Compilation réussie.${C_RESET}"
}

# Lance le serveur en arrière-plan
start_server() {
    ./$SERVER_BIN > $SERVER_LOG 2>&1 &
    server_pid=$!
    # Laisse un court instant au serveur pour se lancer et afficher son PID
    sleep 0.2
    if ! ps -p $server_pid > /dev/null; then
        print_failure "Le serveur n'a pas pu démarrer." "Vérifiez la sortie du serveur dans $SERVER_LOG."
        cat $SERVER_LOG
        server_pid=0
        return 1
    fi
    # Extrait le PID affiché par le serveur lui-même
    displayed_pid=$(grep -o '[0-9]\+' $SERVER_LOG | head -n 1)
    if [ -z "$displayed_pid" ]; then
        print_failure "Le serveur n'a pas affiché son PID." "Le serveur doit afficher son PID au démarrage pour que le client puisse s'y connecter."
        return 1
    fi
    echo "Serveur lancé avec le PID: $displayed_pid"
    return 0
}

# Vérifie si Valgrind est installé
check_valgrind() {
    if command -v valgrind &> /dev/null; then
        valgrind_installed=true
        echo -e "${C_GREEN}Valgrind est installé. Les tests de mémoire seront effectués.${C_RESET}"
    else
        echo -e "${C_YELLOW}Valgrind n'est pas installé. Les tests de mémoire (10, 11) seront ignorés.${C_RESET}"
    fi
}

# --- Définition des Tests ---

# Test 1: Message simple
test_1() {
    print_header 1 "Message simple"
    start_server || return
    local msg="Hello Minitalk!"
    timeout $TIMEOUT_DURATION ./$CLIENT_BIN $displayed_pid "$msg"
    sleep 0.5 # Laisse le temps au serveur de traiter
    if grep -qF "$msg" "$SERVER_LOG"; then
        print_success "Le message simple a été reçu correctement."
    else
        print_failure "Le message simple n'a pas été reçu ou est incorrect." "Vérifiez la logique de reconstruction des caractères bit par bit."
        echo "Attendu: '$msg' | Reçu (contenu du log):"
        cat $SERVER_LOG
    fi
    cleanup_after_test
}

# Test 2: Message long
test_2() {
    print_header 2 "Message long (1000 caractères)"
    start_server || return
    local msg
    msg=$(head /dev/urandom | tr -dc 'A-Za-z0-9' | head -c 1000)
    timeout $TIMEOUT_DURATION ./$CLIENT_BIN $displayed_pid "$msg"
    sleep 1 # Laisse plus de temps pour un message long
    if grep -qF "$msg" "$SERVER_LOG"; then
        print_success "Le message long a été reçu correctement."
    else
        print_failure "Le message long n'a pas été reçu ou est corrompu." "Votre serveur gère-t-il correctement les chaînes de grande taille ? L'allocation de mémoire est-elle dynamique ?"
    fi
    cleanup_after_test
}

# Test 3: Caractères spéciaux et Unicode
test_3() {
    print_header 3 "Caractères spéciaux et Unicode"
    start_server || return
    local msg="\"Voix ambiguë d'un cœur qui, au zéphyr, préfère les jattes de kiwis.\" !@#\$%^&*() 測試"
    timeout $TIMEOUT_DURATION ./$CLIENT_BIN $displayed_pid "$msg"
    sleep 1
    if cat "$SERVER_LOG" | grep -qF "$msg"; then
        print_success "Les caractères spéciaux et Unicode ont été gérés correctement."
    else
        print_failure "Les caractères spéciaux/Unicode n'ont pas été gérés." "Assurez-vous de gérer tous les 8 bits d'un char, y compris pour les caractères étendus (UTF-8)."
        echo "Attendu: '$msg' | Reçu (contenu du log):"
        cat $SERVER_LOG
    fi
    cleanup_after_test
}

# Test 4: Messages successifs rapides
test_4() {
    print_header 4 "Messages successifs rapides"
    start_server || return
    local all_ok=true
    for i in {1..5}; do
        local msg="Test message $i"
        timeout $TIMEOUT_DURATION ./$CLIENT_BIN $displayed_pid "$msg"
        sleep 0.1 # Délai très court
    done
    sleep 1
    for i in {1..5}; do
        local msg="Test message $i"
        if ! grep -qF "$msg" "$SERVER_LOG"; then
            print_failure "Le message '$msg' n'a pas été reçu." "Le serveur doit pouvoir traiter des messages entrants sans délai important. Les variables globales sont-elles bien réinitialisées ?"
            all_ok=false
            break
        fi
    done
    if [ "$all_ok" = true ]; then
        print_success "Tous les messages successifs ont été reçus."
    fi
    cleanup_after_test
}

test_5() {
    print_header 5 "Charge extrême (50 000 caractères)"
    start_server || return
    echo "Génération d'un message de 50 000 caractères... (cela peut prendre un instant)"

    local msg
    msg=$(head /dev/urandom | tr -dc 'A-Za-z0-9' | head -c 50000)
    echo "Envoi du message..."
    time_taken=$( (time -p timeout 60s ./$CLIENT_BIN $displayed_pid "$msg") 2>&1 | grep real | awk '{print $2}' )
    echo "Message envoyé en ${time_taken}s."

    sleep 5 # Laisse du temps au serveur
    # Hash du message envoyé
    local sent_hash=$(echo -n "$msg" | sha256sum | awk '{print $1}')
    # Récupération du contenu affiché par le serveur
    local received_content=$(tail -n +2 "$SERVER_LOG" | tr -d '\0')
    # On nettoie uniquement les fins de lignes, pas le contenu interne
    received_content=$(printf "%s" "$received_content" | sed 's/[\r\n]*$//')
    # Hash du contenu reçu
    local received_hash=$(echo -n "$received_content" | sha256sum | awk '{print $1}')
    # Comparaison
    if [ "$sent_hash" == "$received_hash" ]; then
        print_success "Le message de charge extrême a été reçu correctement en ${time_taken}s."
    else
        print_failure "Le message de charge extrême est corrompu." "Vérifie si le serveur ajoute un '\\n' ou modifie les données. Retirer seulement les fins de ligne via sed suffit."
    fi

    cleanup_after_test
}

# Test 7: PID invalide
test_7() {
    print_header 7 "PID invalide"
    local invalid_pid=99999
    while ps -p $invalid_pid > /dev/null; do
        ((invalid_pid++))
    done

    timeout 5s ./$CLIENT_BIN $invalid_pid "test" > /dev/null 2>&1
    local exit_code=$?

    if [ $exit_code -ne 0 ]; then
        print_success "Le client a correctement échoué avec un PID invalide (code de sortie: $exit_code)."
    else
        print_failure "Le client n'a pas renvoyé d'erreur avec un PID invalide." "Le client doit vérifier le retour de la fonction kill(). Un retour de -1 indique une erreur (ex: PID invalide)."
    fi
    cleanup_after_test
}

# Test 8: Arguments incorrects
test_8() {
    print_header 8 "Arguments incorrects"
    local all_ok=true
    local timeout_duration=2

    timeout $timeout_duration ./$SERVER_BIN extra_arg >/dev/null 2>&1
    if [ $? -eq 0 ]; then
        print_failure "Le serveur ne doit pas se lancer avec des arguments." "Vérifiez votre parsing d'arguments (argc != 1)."
        all_ok=false
    elif [ $? -eq 124 ]; then
        print_failure "Le serveur a dépassé le timeout (probablement bloqué)." "Vérifiez votre code, notamment le main(void) qui peut bloquer."
        all_ok=false
    fi

    timeout $timeout_duration ./$CLIENT_BIN >/dev/null 2>&1
    if [ $? -eq 0 ]; then
        print_failure "Client lancé sans argument." "Vérifiez argc != 3."
        all_ok=false
    elif [ $? -eq 124 ]; then
        print_failure "Client sans argument a dépassé le timeout (bloqué)." "Vérifiez votre code."
        all_ok=false
    fi

    timeout $timeout_duration ./$CLIENT_BIN 123 >/dev/null 2>&1
    if [ $? -eq 0 ]; then
        print_failure "Client lancé avec 1 argument." "Vérifiez argc != 3."
        all_ok=false
    elif [ $? -eq 124 ]; then
        print_failure "Client avec 1 argument a dépassé le timeout (bloqué)." "Vérifiez votre code."
        all_ok=false
    fi

    timeout $timeout_duration ./$CLIENT_BIN 123 "msg" "extra" >/dev/null 2>&1
    if [ $? -eq 0 ]; then
        print_failure "Client lancé avec 3 arguments." "Vérifiez argc != 3."
        all_ok=false
    elif [ $? -eq 124 ]; then
        print_failure "Client avec 3 arguments a dépassé le timeout (bloqué)." "Vérifiez votre code."
        all_ok=false
    fi

    if [ "$all_ok" = true ]; then
        print_success "Les programmes gèrent correctement un nombre incorrect d'arguments."
    fi
    cleanup_after_test
}


# Test 9: Arrêt brutal du serveur
test_9() {
    print_header 9 "Arrêt brutal du serveur pendant la transmission"
    start_server || return
    local msg
    msg=$(head -c 5000000 /dev/urandom | tr -dc 'A-Za-z0-9' | head -c 10000)

    timeout $TIMEOUT_DURATION ./$CLIENT_BIN $displayed_pid "$msg" &
    local client_pid=$!

    # Attendre un peu pour que l'envoi commence mais ne se termine pas
    sleep 0.2
    kill -9 $server_pid
    server_pid=0

    wait $client_pid
    local exit_code=$?
    if [ $exit_code -ne 0 ]; then
        print_success "Le client s'est terminé proprement (code: $exit_code) après l'arrêt brutal du serveur."
    else
        print_failure "Le client n'a pas échoué après l'arrêt du serveur." "Il doit détecter l'absence de réponse et s'arrêter."
    fi
    cleanup_after_test
}


# Test 10: Fuites de mémoire (Client)
test_10() {
    print_header 10 "Fuites de mémoire (Client avec Valgrind)"
    if ! $valgrind_installed; then
        print_failure "Valgrind n'est pas installé." "Test ignoré."
        return
    fi
    start_server || return
    valgrind --leak-check=full --error-exitcode=42 ./$CLIENT_BIN $displayed_pid "Test de fuite mémoire" > /dev/null 2>&1
    local exit_code=$?
    if [ $exit_code -eq 42 ]; then
        print_failure "Fuite de mémoire détectée dans le client." "Exécutez 'valgrind --leak-check=full ./client ...' pour plus de détails."
    else
        print_success "Aucune fuite de mémoire détectée dans le client."
    fi
    cleanup_after_test
}

# --- Logique Principale d'Exécution ---

# Nettoyage initial complet
full_cleanup
check_sources
compile_programs
check_valgrind

# Détermine quels tests exécuter
tests_to_run=()
if [ $# -eq 0 ]; then
    # Exécuter tous les tests si aucun argument n'est donné
    for i in {1..11}; do
        tests_to_run+=($i)
    done
else
    tests_to_run=("$@")
fi

# Exécute les tests sélectionnés
for test_num in "${tests_to_run[@]}"; do
    case $test_num in
        1) test_1 ;;
        2) test_2 ;;
        3) test_3 ;;
        4) test_4 ;;
        5) test_5 ;;
        7) test_7 ;;
        8) test_8 ;;
        9) test_9 ;;
        10) test_10 ;;
        *) echo -e "${C_RED}Test invalide: $test_num${C_RESET}" ;;
    esac
done

# --- Résumé Final ---
echo -e "\n${C_BLUE}========================= RÉSUMÉ DES TESTS =========================${C_RESET}"
echo -e "${C_GREEN}Tests réussis: $tests_passed${C_RESET}"
echo -e "${C_RED}Tests échoués: $tests_failed${C_RESET}"
echo -e "${C_BLUE}======================================================================${C_RESET}"

# Le nettoyage final est géré par le 'trap EXIT'

# Quitte avec un code d'erreur si des tests ont échoué
if [ $tests_failed -gt 0 ]; then
    exit 1
fi
exit 0
