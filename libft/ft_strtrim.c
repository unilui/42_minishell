/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 14:41:44 by lufelip2          #+#    #+#             */
/*   Updated: 2022/11/19 14:05:54 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*

Allocates and returns a copy of ’s1’ with the characters specified in ’set’
removed from the beginning and the end of the string.

*/

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		start;
	int		end;
	int		i;

	i = 0;
	start = 0;
	end = ft_strlen(s1);
	while (s1[start] && ft_strrchr(set, s1[start]))
		start++;
	while (end >= 0 && ft_strrchr(set, s1[end]))
		end--;
	if (start < end)
		str = malloc((end - start) + 2);
	else
		str = malloc(1);
	if (str == NULL)
		return (NULL);
	while (start <= end)
		str[i++] = s1[start++];
	str[i] = '\0';
	return (str);
}
