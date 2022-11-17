/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 20:21:25 by lufelip2          #+#    #+#             */
/*   Updated: 2022/10/16 19:37:41 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*

Allocates memory for an array of nmemb elements of size bytes each and
returns a pointer to the allocated memory. The memory is set to zero.

*/

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*arr;

	if (nmemb <= 0 || size <= 0)
		return (NULL);
	else if (size > 2147483647)
		return (NULL);
	arr = malloc(nmemb * size);
	if (arr == NULL)
		return (NULL);
	ft_bzero(arr, (nmemb * size));
	return (arr);
}
