/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 19:23:15 by lufelip2          #+#    #+#             */
/*   Updated: 2022/10/16 19:41:29 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*

Applies the function ’f’ on each character of the string passed as argument,
passing its index as first argument. Each character is passed by address to ’f’
to be modified if necessary.

*/

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	i;

	if (s)
	{
		i = 0;
		while (*s)
			f(i++, s++);
	}
}
