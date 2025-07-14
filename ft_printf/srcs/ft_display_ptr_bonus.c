/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_ptr_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:37:44 by hfandres          #+#    #+#             */
/*   Updated: 2025/05/07 11:25:24 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf_bonus.h"

static char	*set_nil(char *str)
{
	char	*new_str;

	new_str = ft_strdup("(nil)");
	free(str);
	return (new_str);
}

static char	*itohexstr(unsigned long long nbr)
{
	char			*base16;
	unsigned int	len;
	unsigned int	i;
	char			*str;
	char			*temp;

	len = countnbr_base(nbr);
	i = len;
	str = malloc (sizeof(char) * len + 3);
	base16 = "0123456789abcdef";
	while (i--)
	{
		str[i] = base16[nbr % 16];
		nbr /= 16;
	}
	str[len] = '\0';
	temp = ft_strdup(str);
	free(str);
	str = ft_strjoin("0x", temp);
	free(temp);
	return (str);
}

int	display_ptr(va_list args, char *param)
{
	char				*str;
	int					len;
	unsigned long long	arg;

	arg = va_arg(args, unsigned long long);
	str = NULL;
	if (arg == 0)
		str = set_nil(str);
	else
		str = itohexstr((unsigned long long)arg);
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
