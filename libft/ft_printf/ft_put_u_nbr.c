/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_u_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:44:15 by lufelip2          #+#    #+#             */
/*   Updated: 2022/10/16 19:46:43 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

/*

Outputs the unsigned int 'nbr' to the standard output and returns de amount of
digits outputted.

*/

int	ft_put_u_nbr(unsigned int nbr)
{
	static int	wrt;
	static int	track;
	int			tmp;

	if (nbr > 9)
	{
		track++;
		ft_put_u_nbr(nbr / 10);
	}
	wrt += ft_putchar((nbr % 10) + '0');
	if (track == 0)
	{
		tmp = wrt;
		wrt = 0;
		return (tmp);
	}
	return (track--);
}
