/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_hex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:31:10 by hfandres          #+#    #+#             */
/*   Updated: 2025/05/07 10:45:50 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static char	*itohexstr(unsigned int nbr, char type)
{
	char	*base16;
	int		len;
	int		i;
	char	*str;

	len = countnbr_base(nbr);
	i = len;
	base16 = "";
	str = malloc (sizeof(char) * len + 1);
	if (type == 'x')
		base16 = "0123456789abcdef";
	else if (type == 'X')
		base16 = "0123456789ABCDEF";
	while (i--)
	{
		str[i] = base16[(nbr % 16)];
		nbr /= 16;
	}
	str[len] = '\0';
	return (str);
}

int	display_nbr_hexup(va_list args)
{
	char	*str;
	int		len;
	int		arg;

	arg = va_arg(args, int);
	str = itohexstr(arg, 'X');
	len = ft_strlen(str);
	ft_putstr_fd(str, 1);
	free(str);
	return (len);
}

int	display_nbr_hex(va_list args)
{
	char	*str;
	int		len;
	int		arg;

	arg = va_arg(args, int);
	str = itohexstr(arg, 'x');
	len = ft_strlen(str);
	ft_putstr_fd(str, 1);
	free(str);
	return (len);
}
