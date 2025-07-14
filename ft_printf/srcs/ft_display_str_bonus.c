/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_str_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:26:04 by hfandres          #+#    #+#             */
/*   Updated: 2025/05/05 14:58:33 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf_bonus.h"

static void	*handle_s_flag(char *param, void *arg, int precision)
{
	char	*final_arg;

	final_arg = ft_strdup(arg);
	if (ft_strchr(param, '.'))
	{
		if (ft_strncmp(arg, "(null)", 6) == 0)
		{
			if (precision < 6)
			{
				free(final_arg);
				final_arg = ft_strdup("");
			}
		}
		else if (precision < ft_strlen(arg))
		{
			free(final_arg);
			final_arg = ft_substr(arg, 0, precision);
		}
	}
	if (ft_isdigit(*param) || ft_strchr(param, '-'))
		final_arg = handle_width(param, final_arg);
	free(arg);
	return (final_arg);
}

int	display_str(va_list args, char *param)
{
	char	*arg;
	int		len;
	char	*new_arg;
	int		precision;

	arg = va_arg(args, char *);
	new_arg = NULL;
	len = 0;
	if (!arg)
		arg = "(null)";
	new_arg = ft_strdup(arg);
	while (*param && *param != '.' && !ft_isdigit(*param) && *param != '-')
		param++;
	if (ft_strchr(param, '.'))
		precision = ft_atoi(ft_strchr(param, '.') + 1);
	if (!arg && precision < 6 && ft_strchr(param, '.'))
		precision = 0;
	if (ft_isdigit(*param) || ft_strchr(param, '.') || ft_strchr(param, '-'))
		new_arg = handle_s_flag(param, new_arg, precision);
	len = ft_strlen(new_arg);
	ft_putstr_fd(new_arg, 1);
	free(new_arg);
	return (len);
}
