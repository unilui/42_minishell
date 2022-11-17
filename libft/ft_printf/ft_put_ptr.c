/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_ptr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 17:49:46 by lufelip2          #+#    #+#             */
/*   Updated: 2022/10/16 19:46:33 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

/*

Outputs the pointer 'ptr' to the standard output in hexadecimal format and
returns de amount of digits outputted.

*/

int	ft_put_ptr(size_t ptr, char chr)
{
	const char	*base = "ABCDEF";
	static int	wrt;
	static int	track;
	int			tmp;
	int			lower_case;

	lower_case = 0;
	if (chr == 'x')
		lower_case = 32;
	if (ptr > 15)
	{
		track++;
		ft_put_ptr((ptr / 16), chr);
	}
	if (ptr % 16 > 9)
		wrt += ft_putchar(base[(ptr % 16) - 10] + lower_case);
	else
		wrt += ft_putchar((ptr % 16) + '0');
	if (track == 0)
	{
		tmp = wrt;
		wrt = 0;
		return (tmp);
	}
	return (track--);
}
