/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 20:54:10 by lufelip2          #+#    #+#             */
/*   Updated: 2022/09/13 01:11:20 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	replace_chr(t_str *str)
{
	char	chr_arg;

	chr_arg = va_arg(str->args, int);
	str->written += ft_putchar(chr_arg);
}

void	replace_str(t_str *str)
{
	char	*str_arg;

	str_arg = va_arg(str->args, char *);
	if (!str_arg)
		str->written += ft_putstr("(null)");
	else
		str->written += ft_putstr(str_arg);
}

void	skip_replace(t_str *str)
{
	str->written += ft_putchar(str->chr);
}
