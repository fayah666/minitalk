/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:23:18 by hfandres          #+#    #+#             */
/*   Updated: 2025/07/14 15:31:28 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>
#include <signal.h>

void	get_sig(int sig)
{
	if (sig == 2)
	{
		ft_printf ("yu get SIGINT [%d]\n", sig);
		exit (0);
	}
}
int	main(void)
{
	ft_printf("PID : %d\n", getpid());
	signal (2, get_sig);
	while (1)
	{
        write(STDOUT_FILENO, "En attente...\n", 14);
        sleep(5);
    }
	return (0);
}