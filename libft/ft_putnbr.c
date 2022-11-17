/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 19:52:33 by lufelip2          #+#    #+#             */
/*   Updated: 2022/10/16 19:40:10 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*

Outputs the integer n to the standard output.

*/

int	ft_putnbr(int nbr)
{
	static int	wrt;
	static int	track;
	int			tmp;

	if (nbr < -9 || nbr > 9)
	{
		track++;
		ft_putnbr(nbr / 10);
	}
	if (nbr >= -9 && nbr < 0)
		wrt += ft_putchar('-');
	if (nbr < 0)
		wrt += ft_putchar(-(nbr % 10) + '0');
	else
		wrt += ft_putchar((nbr % 10) + '0');
	if (track == 0)
	{
		tmp = wrt;
		wrt = 0;
		return (tmp);
	}
	return (track--);
}
