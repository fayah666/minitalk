/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:26:04 by hfandres          #+#    #+#             */
/*   Updated: 2025/05/07 10:48:17 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	display_str(va_list args)
{
	char	*arg;
	int		len;
	char	*new_arg;

	arg = va_arg(args, char *);
	new_arg = NULL;
	if (!arg)
		arg = "(null)";
	new_arg = ft_strdup(arg);
	len = ft_strlen(new_arg);
	ft_putstr_fd(new_arg, 1);
	free(new_arg);
	return (len);
}
