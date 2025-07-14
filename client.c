/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:43:43 by hfandres          #+#    #+#             */
/*   Updated: 2025/07/14 15:11:35 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <signal.h>
#include <stdlib.h>

int	main(int ac, char **av)
{
	if (ac < 2 || ac > 4)
	{
		ft_printf("USAGE : %s <SERVER_PID> <string>\n", av[0]);
		return (0);
		
	}
	else
	{
		ft_printf ("send %s to %s", av[1], av[2]);
		kill (atoi(av[1]), atoi(av[2]));	
	}
	return (0);
}