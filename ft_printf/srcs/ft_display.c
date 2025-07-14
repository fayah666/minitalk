/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:54:59 by hfandres          #+#    #+#             */
/*   Updated: 2025/05/07 11:24:46 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	display(va_list args, char *param)
{
	int		len;
	t_put	put[127];

	len = 0;
	if (get_id(param) == '%')
		return (free(param), display_percent());
	put['c'] = display_char;
	put['s'] = display_str;
	put['d'] = display_nbr;
	put['i'] = display_nbr;
	put['u'] = display_nbru;
	put['p'] = display_ptr;
	put['x'] = display_nbr_hex;
	put['X'] = display_nbr_hexup;
	len = put[(unsigned int)get_id(param)](args);
	free(param);
	return (len);
}
