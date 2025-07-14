/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_char_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:32:10 by hfandres          #+#    #+#             */
/*   Updated: 2025/05/07 10:29:17 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf_bonus.h"

int	display_char(va_list args, char *param)
{
	int				len;
	unsigned int	arg;
	char			*str;

	len = 0;
	str = ft_strdup("");
	arg = va_arg(args, unsigned int);
	while (*param && *param != '.' && !ft_isdigit(*param) && *param != '-')
		param++;
	if (ft_strchr(param, '-') || ft_isdigit(*param))
		str = handle_flag(param, str);
	len += ft_strlen(str);
	if (ft_strchr(param, '-'))
	{
		ft_putchar_fd(arg, 1);
		ft_putstr_fd(str, 1);
	}
	else
	{
		ft_putstr_fd(str, 1);
		ft_putchar_fd(arg, 1);
	}
	free(str);
	return (len + 1);
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
