/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 18:50:27 by lufelip2          #+#    #+#             */
/*   Updated: 2022/10/16 19:45:51 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*

Fills the first n bytes of the memory area pointed to by s with
the constant byte c

*/

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*us_s;

	i = 0;
	us_s = (unsigned char *)s;
	while (i < n)
		us_s[i++] = c;
	return (s);
}
