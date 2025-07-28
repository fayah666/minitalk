/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:43:43 by hfandres          #+#    #+#             */
/*   Updated: 2025/07/28 03:14:14 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <signal.h>
#include <unistd.h>

static int	g_received = 0;

void	handle_sig(int sig)
{
	if (sig == SIGUSR1)
		g_received = 1;
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
	while (*str)
	{
		send_char(server_pid, *str);
		str++;
	}
	send_char(server_pid, '\0');
	return (0);
}
