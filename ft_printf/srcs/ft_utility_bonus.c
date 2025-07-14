/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utility_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:07:36 by hfandres          #+#    #+#             */
/*   Updated: 2025/04/29 10:26:16 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/ft_printf_bonus.h"

char	*set(int precision, char c)
{
	char	*set;

	if (precision < 0)
		precision = 0;
	set = malloc(sizeof(char) * (precision + 1));
	if (!set)
		return (NULL);
	set[precision] = '\0';
	ft_memset(set, c, precision);
	return (set);
}

int	is_format_id(const unsigned char c)
{
	char	*id;
	char	*flag;

	id = "dicsupxX%";
	flag = " .0-+#";
	if (ft_strchr(id, c))
		return (e_id);
	else if (ft_strchr(flag, c))
		return (e_flag);
	else if (ft_isdigit(c))
		return (e_dig);
	return (-1);
}

char	get_id(char *param)
{
	char	*id;

	id = "dicsupxX%";
	while (*param)
	{
		if (ft_strchr(id, *param))
			return (*param);
		param++;
	}
	return (-1);
}

int	countnbr_base(unsigned long long nbr)
{
	int	count;

	count = 0;
	if (nbr / 16 > 0)
		count += countnbr_base(nbr / 16);
	nbr %= 16;
	if (nbr % 16 >= 10)
		count++;
	else
		count++;
	return (count);
}
