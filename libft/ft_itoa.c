/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:28:00 by lufelip2          #+#    #+#             */
/*   Updated: 2022/10/16 19:45:26 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*

Returns the absolute value of 'nbr'. '-1' becomes '1'.

*/

static int	ft_abs(int nbr)
{
	if (nbr < 0)
		return (-nbr);
	return (nbr);
}

/*

Allocates and returns a string representing the integer received as an
argument. Negative numbers must be handled.

*/

char	*ft_itoa(int n)
{
	char	*nbr;
	int		digits;
	int		i_nbr;

	digits = 1;
	i_nbr = n;
	while (i_nbr < -9 || i_nbr > 9)
	{
		i_nbr /= 10;
		digits++;
	}
	nbr = malloc(digits + (n < 0) + 1);
	if (nbr == NULL)
		return (NULL);
	if (n < 0)
		nbr[0] = '-';
	nbr[digits + (n < 0)] = '\0';
	while (digits--)
	{
		nbr[digits + (n < 0)] = ft_abs(n % 10) + '0';
		n /= 10;
	}
	return (nbr);
}
