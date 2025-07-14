/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_nbr_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:33:04 by hfandres          #+#    #+#             */
/*   Updated: 2025/05/07 10:46:08 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf_bonus.h"

int	display_nbr(va_list args, char *param)
{
	char	*str;
	int		len;
	int		arg;
	char	*temp;

	arg = va_arg(args, int);
	len = 0;
	str = ft_itoa(arg);
	if (ft_strchr(param, '+') && arg >= 0)
	{
		temp = ft_strdup(str);
		free(str);
		str = ft_strjoin("+", temp);
		free(temp);
	}
	while (*param && *param != '.' && !ft_isdigit(*param) && *param != '-' && \
			*param != '0' && !ft_strchr(param, ' '))
		param++;
	if (ft_strchr(param, '.') || ft_strchr(param, '-') || \
			ft_isdigit(*param) || ft_strchr(param, ' '))
		str = handle_flag(param, str);
	len = ft_strlen(str);
	ft_putstr_fd(str, 1);
	free(str);
	return (len);
}
