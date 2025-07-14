/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:32:10 by hfandres          #+#    #+#             */
/*   Updated: 2025/04/25 15:29:13 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	display_char(va_list args)
{
	unsigned int	arg;

	arg = va_arg(args, unsigned int);
	ft_putchar_fd(arg, 1);
	return (1);
}

int	display_default_char(char c)
{
	ft_putchar_fd(c, 1);
	return (1);
}

int	display_percent(void)
{
	ft_putchar_fd('%', 1);
	return (1);
}
