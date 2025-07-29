/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:43:43 by hfandres          #+#    #+#             */
/*   Updated: 2025/07/29 11:08:59 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file client.c
 * @brief Client program for sending messages to a server using UNIX signals
 *
 * This program implements a client that sends messages to a server character by
 * character using UNIX signals (SIGUSR1 and SIGUSR2). Each character is sent
 * bit by bit, with SIGUSR1 representing 1 and SIGUSR2 representing 0.
 *
 * Global variables:
 * @var g_received - Flag to track signal acknowledgment from server
 *
 * Functions:
 * @fn handle_sig - Signal handler for receiving server acknowledgments
 * @param sig Signal number received (SIGUSR1 or SIGUSR2)
 *
 * @fn send_char - Sends a single character to the server bit by bit
 * @param pid Process ID of the server
 * @param c Character to be sent
 *
 * @fn main - Entry point of the program
 * @param ac Argument count
 * @param av Argument vector (expects server PID and message string)
 * @return 0 on success, 1 on error
 *
 * Usage: ./client <SERVER_PID> <STRING_TO_PASS>
 */

#include "ft_printf.h"
#include <signal.h>
#include <unistd.h>

static int	g_received = 0;

void	handle_sig(int sig)
{
	if (sig == SIGUSR1)
		g_received = 1;
	if (sig == SIGUSR2)
	{
		ft_printf("Message received by server.\n");
		g_received = 1;
	}
}

void	send_char(int pid, char c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		g_received = 0;
		if ((c >> (7 - i)) & 1)
		{
			if (kill(pid, SIGUSR1) == -1)
				return ;
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				return ;
		}
		while (!g_received)
			pause();
		i++;
	}
}

int	main(int ac, char **av)
{
	char	*str;
	int		server_pid;

	if (ac != 3)
	{
		ft_printf("USAGE : %s <SERVER_PID> <STRING_TO_PASS>\n", av[0]);
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
