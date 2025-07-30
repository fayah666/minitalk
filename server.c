/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:23:18 by hfandres          #+#    #+#             */
/*   Updated: 2025/07/30 12:48:48 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_C_SOURCE 199309L
#include "ft_printf/includes/ft_printf.h"
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

static void	print_msg(t_list *msg)
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
	if (!msg)
		init_list(&msg);
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

static void	init_action(struct sigaction *act)
{
	ft_memset(act, 0, sizeof(*act));
	act->sa_sigaction = handle_msg;
	sigemptyset(&act->sa_mask);
	act->sa_flags = SA_SIGINFO;
}

int	main(int ac, char **av)
{
	struct sigaction	act;

	(void) av;
	if (ac != 1)
	{
		ft_printf("Usage: ./server\n");
		return (1);
	}
	ft_printf("PID : %d\n", getpid());
	init_action(&act);
	if (sigaction(SIGUSR1, &act, NULL) == -1)
		return (1);
	if (sigaction(SIGUSR2, &act, NULL) == -1)
		return (1);
	while (1)
		pause();
	return (0);
}
