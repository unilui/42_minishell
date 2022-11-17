/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_x_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 02:54:44 by lufelip2          #+#    #+#             */
/*   Updated: 2022/10/16 19:46:53 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

/*

Outputs the unsigned int 'nbr' to the standard output in hexadecimal format and
returns de amount of digits outputted.

*/

int	ft_put_x_nbr(unsigned int nbr, char chr)
{
	const char	*base = "ABCDEF";
	static int	wrt;
	static int	track;
	int			tmp;
	int			lower_case;

	lower_case = 0;
	if (chr == 'x')
		lower_case = 32;
	if (nbr > 15)
	{
		track++;
		ft_put_x_nbr((nbr / 16), chr);
	}
	if (nbr % 16 > 9)
		wrt += ft_putchar(base[(nbr % 16) - 10] + lower_case);
	else
		wrt += ft_putchar((nbr % 16) + '0');
	if (track == 0)
	{
		tmp = wrt;
		wrt = 0;
		return (tmp);
	}
	return (track--);
}
