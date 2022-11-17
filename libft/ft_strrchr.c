/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 18:46:28 by lufelip2          #+#    #+#             */
/*   Updated: 2022/10/16 19:43:20 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*

Returns a pointer to the last occurrence  of the character c in the string s.

*/

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	s += i;
	while (i >= 0)
	{
		if (*s == (char)c)
			return ((char *)s);
		else
			s--;
		i--;
	}
	return (NULL);
}
