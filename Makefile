CC      = cc
RM      = rm -rf
CFLAGS  = -Wall -Wextra -Werror -Ift_printf/includes
LFTPRINTF = ft_printf/libftprintf.a

CLIENT  = client
SERVER  = server

CLIENT_SRC = client.c
SERVER_SRC = server.c list/list.c

CLIENT_BONUS_SRC = client_bonus.c
SERVER_BONUS_SRC = server_bonus.c list/list.c

CLIENT_OBJ = $(CLIENT_SRC:.c=.o)
SERVER_OBJ = $(SERVER_SRC:.c=.o)

CLIENT_BONUS_OBJ = $(CLIENT_BONUS_SRC:.c=.o)
SERVER_BONUS_OBJ = $(SERVER_BONUS_SRC:.c=.o)

all: $(CLIENT) $(SERVER)

$(CLIENT): $(CLIENT_OBJ) $(LFTPRINTF)
	$(CC) $(CFLAGS) $(CLIENT_OBJ) $(LFTPRINTF) -o $(CLIENT)

$(SERVER): $(SERVER_OBJ) $(LFTPRINTF)
	$(CC) $(CFLAGS) $(SERVER_OBJ) $(LFTPRINTF) -o $(SERVER)

bonus : $(CLIENT_BONUS_OBJ) $(SERVER_BONUS_OBJ) $(LFTPRINTF)
		$(CC) $(CFLAGS) $(CLIENT_BONUS_OBJ) $(LFTPRINTF) -o $(CLIENT)
		$(CC) $(CFLAGS) $(SERVER_BONUS_OBJ) $(LFTPRINTF) -o $(SERVER)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LFTPRINTF):
	make -C ft_printf

clean:
	make clean -C ft_printf
	$(RM) $(CLIENT_OBJ) $(SERVER_OBJ)
	$(RM) $(CLIENT_BONUS_OBJ) $(SERVER_BONUS_OBJ)

fclean: clean
	make fclean -C ft_printf
	$(RM) $(CLIENT) $(SERVER)

re: fclean all

test: all
	@echo "\n=== Starting Server ==="
	@./server & echo "Server PID: $$!"
	@sleep 1
	@echo "\n=== Testing Client ==="
	@./client `pgrep server` "Hello World!"
	@echo "\n=== Cleaning Up ==="
	@pkill server
	@make fclean
	@echo "Test completed!\n"

valgrind: all
	@echo "\n=== Testing Server with Valgrind ==="
	@valgrind --leak-check=full \
		--show-leak-kinds=all \
		--track-origins=yes \
		--verbose \
		--log-file=valgrind_server.log \
		./server & \
	SERVER_PID=$$! && \
	sleep 1 && \
	echo "\n=== Testing Client with Valgrind ===" && \
	valgrind --leak-check=full \
		--show-leak-kinds=all \
		--track-origins=yes \
		--verbose \
		--log-file=valgrind_client.log \
		./client $$SERVER_PID "Test Message" && \
	sleep 1 && \
	kill $$SERVER_PID && \
	echo "\n=== Valgrind Logs Created ==="
	@make fclean
	@echo "Check valgrind_server.log and valgrind_client.log for results"

clean_valgrind:
	@echo "Cleaning Valgrind logs..."
	$(RM) valgrind_server.log valgrind_client.log

.PHONY: all bonus clean fclean re test valgrind