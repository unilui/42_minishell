/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 20:35:57 by lufelip2          #+#    #+#             */
/*   Updated: 2022/10/16 19:42:13 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*

Appends the NUL-terminated string src to the end of dst.  It will append at
most size - strlen(dst) - 1 bytes, NUL-terminating the result.

*/

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len_dst;
	size_t	len_src;

	i = 0;
	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	if (size == 0)
		return (len_src);
	else if (size <= len_dst)
		return (len_src + size);
	else if (len_dst >= 1 || (sizeof(dst) >= 1 && len_dst == 0))
	{
		while (i < (size - len_dst - 1) && src[i])
		{
			dst[len_dst + i] = src[i];
			i++;
		}
		dst[len_dst + i] = '\0';
	}
	return (len_dst + len_src);
}
