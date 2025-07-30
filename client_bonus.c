/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:43:43 by hfandres          #+#    #+#             */
/*   Updated: 2025/07/30 14:07:29 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/includes/ft_printf.h"
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
		g_received = 2;
	}
}

int	wait_ack(void)
{
	int	tries;

	tries = 0;
	while (g_received == 0)
	{
		usleep(1000);
		tries++;
		if (tries > 100)
			return (-1);
	}
	return (0);
}

int	send_char(int pid, char c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		g_received = 0;
		if ((c >> (7 - i)) & 1)
		{
			if (kill(pid, SIGUSR1) == -1)
				return (-1);
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				return (-1);
		}
		if (wait_ack() == -1)
			return (-1);
		i++;
	}
	return (0);
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
		if (send_char(server_pid, *str) == -1)
			return (ft_printf("Error: server doesn't respond\n"));
		str++;
	}
	send_char(server_pid, '\0');
	return (0);
}
