/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 11:23:47 by hfandres          #+#    #+#             */
/*   Updated: 2025/05/09 10:02:37 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "../libft/libft.h" 
# include <stdlib.h>

typedef int	(*t_put)(va_list args);

int		is_format_id(const unsigned char c);
int		ft_printf(const char *format, ...);
int		display_default_char(char c);
int		display_percent(void);
int		display_char(va_list args);
int		display(va_list args, char *param);
int		display_str(va_list args);
int		display_ptr(va_list args);
int		display_nbru(va_list args);
int		display_nbr(va_list args);
int		display_nbr_hex(va_list args);
int		display_nbr_hexup(va_list args);
char	get_id(char *param);
int		countnbr_base(unsigned long long nbr);
#endif
