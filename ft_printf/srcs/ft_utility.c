/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utility.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:07:36 by hfandres          #+#    #+#             */
/*   Updated: 2025/05/09 09:55:17 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/ft_printf.h"

int	is_format_id(const unsigned char c)
{
	char	*id;

	id = "dicsupxX%";
	if (ft_strchr(id, c))
		return (1);
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
