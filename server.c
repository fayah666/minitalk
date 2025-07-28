/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:23:18 by hfandres          #+#    #+#             */
/*   Updated: 2025/07/28 02:36:27 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <signal.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

static void	handle_msg(int sig, siginfo_t *info, void *context)
{
	static int	bit = 0;
	static char	c = 0;
	static char	msg[134000];
	static int	i = 0;

	(void)context;
	if (sig == SIGUSR1)
		c |= (1 << (7 - bit));
	bit++;
	if (bit == 8)
	{
		msg[i++] = c;
		if (c == '\0')
		{
			ft_printf("%s\n", msg);
			i = 0;
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

