/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 20:31:22 by lufelip2          #+#    #+#             */
/*   Updated: 2022/10/16 19:38:59 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*

Scans the initial n bytes of the memory area pointed to by s for the first
instance of c.

*/

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*uc_s;

	i = 0;
	uc_s = (unsigned char *)s;
	while (i < n)
	{
		if (*uc_s == (unsigned char)c)
			return ((void *)uc_s);
		else
			uc_s++;
		i++;
	}
	return (NULL);
}
