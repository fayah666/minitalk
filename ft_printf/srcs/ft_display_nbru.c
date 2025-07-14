/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_nbru.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:34:04 by hfandres          #+#    #+#             */
/*   Updated: 2025/05/07 10:47:05 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	count_nbru(unsigned int n)
{
	int	len;

	len = 0;
	if (n >= 10)
		len += count_nbru(n / 10);
	n %= 10;
	len++;
	return (len);
}

static char	*itou(unsigned int n)
{
	char	*str;
	int		len;
	int		i;

	len = count_nbru(n);
	i = len;
	str = malloc(sizeof(char) * len +1);
	while (i--)
	{
		str[i] = (n % 10) + 48;
		n /= 10;
	}
	str[len] = 0;
	return (str);
}

int	display_nbru(va_list args)
{
	int				len;
	unsigned int	arg;
	char			*str;

	arg = va_arg(args, unsigned int);
	len = count_nbru(arg);
	str = itou((unsigned int)arg);
	len = ft_strlen(str);
	ft_putstr_fd(str, 1);
	free(str);
	return (len);
}
