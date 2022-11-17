/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_nbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 21:10:10 by lufelip2          #+#    #+#             */
/*   Updated: 2022/09/13 01:11:28 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	replace_int(t_str *str)
{
	int	nbr_arg;

	nbr_arg = va_arg(str->args, int);
	str->written += ft_putnbr(nbr_arg);
}

void	replace_uint(t_str *str)
{
	unsigned int	nbr_arg;

	nbr_arg = va_arg(str->args, unsigned int);
	str->written += ft_put_u_nbr(nbr_arg);
}

void	replace_hexa(t_str *str)
{
	unsigned int	nbr_arg;

	nbr_arg = va_arg(str->args, unsigned int);
	str->written += ft_put_x_nbr(nbr_arg, str->chr);
}

void	replace_ptr(t_str *str)
{
	size_t	ptr_arg;

	ptr_arg = va_arg(str->args, size_t);
	if (ptr_arg == 0)
		str->written += ft_putstr("(nil)");
	else
	{
		str->written += ft_putstr("0x");
		str->written += ft_put_ptr(ptr_arg, 'x');
	}
}
