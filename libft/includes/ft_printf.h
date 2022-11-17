/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 01:08:27 by lufelip2          #+#    #+#             */
/*   Updated: 2022/09/15 19:07:34 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>

typedef struct s_str {
	char	chr;
	int		written;
	va_list	args;
}	t_str;

typedef void	(*t_replace)(t_str *str);

t_replace	placeholder(char placeholder);
void		replace_handler(t_str *str);
void		replace_uint(t_str *str);
void		replace_hexa(t_str *str);
void		replace_chr(t_str *str);
void		replace_int(t_str *str);
void		replace_str(t_str *str);
void		replace_ptr(t_str *str);
void		skip_replace(t_str *str);
int			ft_put_ptr(size_t ptr, char chr);
int			ft_put_u_nbr(unsigned int nbr);
int			ft_put_x_nbr(unsigned int nbr, char chr);

#endif
