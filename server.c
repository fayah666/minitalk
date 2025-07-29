/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:23:18 by hfandres          #+#    #+#             */
/*   Updated: 2025/07/29 11:08:19 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file server.c
 * @brief Server component of a simple client-server communication system using UNIX signals
 *
 * This program implements a server that receives messages from clients using UNIX signals
 * (SIGUSR1 and SIGUSR2). It reconstructs characters bit by bit from the received signals
 * and stores them in a linked list until a complete message is received.
 *
 * @functions
 * static void init_list(t_list **msg)
 *     Initializes a new linked list if the provided list pointer is NULL
 *
 * static void print_msg(t_list *msg)
 *     Prints and frees the stored message if the list is not empty
 *
 * static void handle_msg(int sig, siginfo_t *info, void *context)
 *     Signal handler that processes incoming SIGUSR1 and SIGUSR2 signals
 *     Reconstructs characters bit by bit and stores them in a linked list
 *     Sends acknowledgment signals back to the client
 *
 * int main(void)
 *     Sets up signal handlers and enters an infinite loop waiting for signals
 *     Displays the server's PID on startup
 *
 * @signals
 * - SIGUSR1: Represents a '1' bit
 * - SIGUSR2: Represents a '0' bit
 *
 * @note The server acknowledges each received bit with SIGUSR1
 * @note When a complete message is received (null terminator), the server sends SIGUSR2
 */

#define _POSIX_C_SOURCE 199309L
#include "ft_printf.h"
#include <unistd.h>
#include <signal.h>
#include "list/list.h"

static void	init_list(t_list **msg)
{
	if (!*msg)
	{
		*msg = list_init();
		if (!*msg)
			return ;
	}
}

static void print_msg(t_list *msg)
{
	if (msg && !list_is_empty(msg))
	{
		list_print(msg);
		list_free(msg);
		free(msg);
	}
}

static void	handle_msg(int sig, siginfo_t *info, void *context)
{
	static int		bit = 0;
	static char		c = 0;
	static t_list	*msg = NULL;

	(void)context;
	init_list(&msg);
	if (!msg)
		return ;
	if (sig == SIGUSR1)
		c |= (1 << (7 - bit));
	if (++bit == 8)
	{
		push_back(msg, c);
		if (c == '\0')
		{
			print_msg(msg);
			msg = NULL;
			if (kill(info->si_pid, SIGUSR2) == -1)
				return ;
		}
		bit = 0;
		c = 0;
	}
	if (kill(info->si_pid, SIGUSR1) == -1)
		return ;
}

int	main(void)
{
	struct sigaction	act;

	ft_printf("PID : %d\n", getpid());
	ft_memset(&act, 0, sizeof(act));
	act.sa_sigaction = handle_msg;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &act, NULL) == -1)
		return (1);
	if (sigaction(SIGUSR2, &act, NULL) == -1)
		return (1);
	while (1)
		pause();
	return (0);
}
