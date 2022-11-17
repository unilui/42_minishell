/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chrpst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 03:44:34 by lufelip2          #+#    #+#             */
/*   Updated: 2022/10/16 19:37:45 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*

Returns the index of the first occurrence of the character c in the string s.

*/

int	ft_chrpst(char const *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	while (*s)
	{
		if (*s == (char)c)
			return (i);
		s++;
		i++;
	}
	if (*s == (char)c)
		return (i);
	return (-1);
}
