/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 11:23:47 by hfandres          #+#    #+#             */
/*   Updated: 2025/05/09 10:07:56 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H

# include <stdarg.h>
# include "../libft/libft.h" 
# include <stdlib.h>

enum e_type
{
	e_id,
	e_flag,
	e_dig
};

typedef int	(*t_put)(va_list args, char *param);

int		is_format_id(const unsigned char c);
int		ft_printf(const char *format, ...);
int		display_default_char(char c);
int		display_percent(void);
int		display_char(va_list args, char *param);
int		display(va_list args, char *param);
int		display_str(va_list args, char *param);
int		display_ptr(va_list args, char *param);
int		display_nbru(va_list args, char *param);
int		display_nbr(va_list args, char *param);
int		display_nbr_hex(va_list args, char *param);
char	get_id(char *param);
int		countnbr_base(unsigned long long nbr);
char	*set(int precision, char c);
char	*handle_zero(char *param, char *arg);
char	*handle_width(char *param, char *arg);
char	*handle_precision(char *param, char *arg);
char	*handle_space(char *arg);
void	*handle_flag(char *param, void *arg);
#endif
