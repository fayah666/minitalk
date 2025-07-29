/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:23:18 by hfandres          #+#    #+#             */
/*   Updated: 2025/07/29 10:40:41 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			list_print(msg);
			list_free(msg);
			free(msg);
			msg = NULL;
			kill(info->si_pid, SIGUSR2);
		}
		bit = 0;
		c = 0;
	}
	kill(info->si_pid, SIGUSR1);
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
