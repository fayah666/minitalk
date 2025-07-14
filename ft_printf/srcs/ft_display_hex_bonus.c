/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_hex_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:31:10 by hfandres          #+#    #+#             */
/*   Updated: 2025/05/07 10:45:18 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf_bonus.h"

static char	*handle_sharp(char *param, char	*str)
{
	char	*new_arg;

	new_arg = NULL;
	if (get_id(param) == 'x')
		new_arg = ft_strjoin("0x", str);
	else
		new_arg = ft_strjoin("0X", str);
	if (!new_arg)
		return (str);
	free(str);
	return (new_arg);
}

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

int	display_nbr_hex(va_list args, char *param)
{
	char	*str;
	int		len;
	int		arg;

	arg = va_arg(args, int);
	str = itohexstr(arg, get_id(param));
	if (ft_strchr(param, '#') && arg != 0)
		str = handle_sharp(param, str);
	while (*param && *param != '.' && !ft_isdigit(*param) && \
			*param != '-' && *param != '0')
		param++;
	if (ft_strchr(param, '.') || ft_strchr(param, '-') || ft_isdigit(*param))
		str = handle_flag(param, str);
	len = ft_strlen(str);
	ft_putstr_fd(str, 1);
	free(str);
	return (len);
}
