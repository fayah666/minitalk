/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:43:43 by hfandres          #+#    #+#             */
/*   Updated: 2025/07/16 13:08:18 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void	send_strlen(int pid, int len)
{
	int	i;

	i = 0;
	while (i < 32)
	{
		if ((len >> (31 - i)) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100);
		i++;
	}
}

void	send_char(int pid, char c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if ((c >> (7 - i)) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100);
		i++;
	}
}

int	main(int ac, char **av)
{
	char	*str;
	int		len;

	if (ac < 2 || ac > 4)
	{
		ft_printf("USAGE : %s <SERVER_PID> <string>\n", av[0]);
		return (0);
	}
	else
	{
		str = av[2];
		len = ft_strlen(str);
		send_strlen(atoi(av[1]), len);
		while (*str)
		{
			send_char(atoi(av[1]), *str);
			str++;
		}
		send_char (atoi(av[1]), '\0');
	}
	return (0);
}
