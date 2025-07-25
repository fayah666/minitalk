/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:43:43 by hfandres          #+#    #+#             */
/*   Updated: 2025/07/25 13:53:14 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

static int g_received = 0;

void handle_sig(int sig)
{
    if (sig == SIGUSR1)
        g_received = 1;
}

void send_char(int pid, char c)
{
    int i;

    i = 0;
    while (i < 8)
    {
	g_received = 0;
        if ((c >> (7 - i)) & 1)
            kill(pid, SIGUSR1);
        else
            kill(pid, SIGUSR2);
        while (!g_received)
            pause();
		i++;
    }
}

int main(int ac, char **av)
{
    char *str;
    int server_pid;

    if (ac != 3)
    {
        ft_printf("USAGE : %s <SERVER_PID> <string>\n", av[0]);
        return (1);
    }
    server_pid = atoi(av[1]);
    if (server_pid <= 0)
    {
        ft_printf("Error: Invalid PID\n");
        return (1);
    }
    str = av[2];
    signal(SIGUSR1, handle_sig);
    signal(SIGUSR2, handle_sig);
    while (*str)
    {
        send_char(server_pid, *str);
        str++;
    }
    send_char(server_pid, '\0');
    return (0);
}
