/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:33:07 by lufelip2          #+#    #+#             */
/*   Updated: 2022/10/16 19:42:01 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*

Allocates and returns a new string, which is the result of
the concatenation of ’s1’ and ’s2’.

*/

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		len;

	if (!s1 && !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	if (s1)
	{
		while (*s1)
			*str++ = *s1++;
	}
	if (s2)
	{
		while (*s2)
			*str++ = *s2++;
	}
	*str = '\0';
	return (str -= len);
}
