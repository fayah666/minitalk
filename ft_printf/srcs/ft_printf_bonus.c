/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 11:17:36 by hfandres          #+#    #+#             */
/*   Updated: 2025/05/09 09:57:19 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stdio.h>
#include "../includes/ft_printf_bonus.h"

static char	*get_param(const char *format)
{
	char	*copy;
	int		len;
	char	*param;

	if (!format)
		return (NULL);
	copy = (char *)format;
	while (*copy && is_format_id(*copy) != e_id)
		copy++;
	len = (copy - format) + 1;
	param = malloc (sizeof(char) * (len + 1));
	if (!param)
		return (NULL);
	ft_memmove(param, format, len);
	param[len] = '\0';
	return (param);
}

static int	display_res(const char *format, va_list vl)
{
	int		len;

	len = 0;
	while (*format)
	{
		if (*format != '%')
			len += display_default_char(*format);
		else if (*format == '%')
		{
			format++;
			len += display(vl, get_param(format));
			while (is_format_id(*format) != e_id)
				format++;
		}
		format++;
	}
	return (len);
}

int	ft_printf(const char *format, ...)
{
	va_list	vl;
	int		len;

	len = 0;
	if (!format)
		return (-1);
	va_start(vl, format);
	len = display_res(format, vl);
	va_end(vl);
	return (len);
}
