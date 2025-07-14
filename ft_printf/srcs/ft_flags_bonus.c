/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:43:52 by hfandres          #+#    #+#             */
/*   Updated: 2025/05/07 11:26:08 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf_bonus.h"

char	*handle_zero(char *param, char *arg)
{
	char	*spaces;
	char	*new_arg;
	int		precision;
	char	nbr_signed[2];
	char	*temp;

	new_arg = NULL;
	nbr_signed[1] = '\0';
	precision = ft_atoi(param) - ft_strlen(arg);
	if (*arg == '-' || *arg == '+')
	{
		nbr_signed[0] = (unsigned int)*arg;
		spaces = set(precision - (ft_strlen(nbr_signed) - 1), '0');
		temp = ft_strjoin(spaces, arg + 1);
		new_arg = ft_strjoin(nbr_signed, temp);
		free(temp);
	}
	else
	{
		spaces = set(precision, '0');
		new_arg = ft_strjoin(spaces, arg);
	}
	free(spaces);
	free(arg);
	return (new_arg);
}

char	*handle_width(char *param, char *arg)
{
	char	*spaces;
	char	*new_arg;
	int		precision;
	int		len;

	new_arg = NULL;
	len = ft_strlen(arg);
	if (ft_strchr(param, '-'))
		precision = ft_atoi(ft_strrchr(param, '-') + 1) - len;
	else
		precision = ft_atoi(param) - len;
	if (precision < 0)
		precision = 0;
	if (get_id(param) == 'c')
		return (free(arg), set(precision - 1, ' '));
	spaces = set(precision, ' ');
	if (ft_strchr(param, '-'))
		new_arg = ft_strjoin(arg, spaces);
	else
		new_arg = ft_strjoin(spaces, arg);
	free(arg);
	free(spaces);
	return (new_arg);
}

char	*handle_precision(char *param, char *arg)
{
	char	*spaces;
	char	*new_arg;
	int		precision;
	char	nbr_signed[2];
	char	*temp;

	new_arg = NULL;
	nbr_signed[1] = '\0';
	precision = ft_atoi(ft_strrchr(param, '.') + 1) - ft_strlen(arg);
	if (*arg == '-' || *arg == '+')
	{
		nbr_signed[0] = (unsigned int)*arg;
		spaces = set(precision + 1, '0');
		temp = ft_strjoin(spaces, arg + 1);
		new_arg = ft_strjoin(nbr_signed, temp);
		free(temp);
	}
	else
	{
		spaces = set(precision, '0');
		new_arg = ft_strjoin(spaces, arg);
	}
	free(arg);
	free(spaces);
	return (new_arg);
}

char	*handle_space(char *arg)
{
	char	*new_arg;

	new_arg = ft_strjoin(" ", arg);
	free(arg);
	return (new_arg);
}

void	*handle_flag(char *param, void *arg)
{
	if (ft_strchr(param, '.'))
	{
		if (ft_strncmp(arg, "0", 2) == 0)
		{
			free(arg);
			arg = handle_precision(param, ft_strdup(""));
		}
		else
			arg = handle_precision(param, arg);
	}
	else if (*param == '0' && get_id(param) != 'c')
		arg = handle_zero(param, arg);
	if (ft_isdigit(*param) || ft_strchr(param, '-'))
		arg = handle_width(param, arg);
	if (ft_strchr(param, ' ') && *(char *)arg != '-')
		arg = handle_space(arg);
	return (arg);
}
