/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 21:06:41 by lufelip2          #+#    #+#             */
/*   Updated: 2022/10/16 19:39:10 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*

Compares the first n bytes (each interpreted as unsigned char) of the memory
areas s1 and s2.

*/

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int				signal;
	int				total;
	size_t			i;
	unsigned char	*u_s1;
	unsigned char	*u_s2;

	i = 0;
	signal = -1;
	total = 0;
	u_s1 = (unsigned char *)s1;
	u_s2 = (unsigned char *)s2;
	while (i < n)
	{
		if (u_s1[i] != u_s2[i])
		{
			if (signal == -1)
				signal = (u_s1[i] - u_s2[i]) < 0;
			total += u_s1[i] - u_s2[i];
		}
		i++;
	}
	if ((total > 0) && signal)
		total *= -1;
	return (total);
}
