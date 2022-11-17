/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 15:51:10 by lufelip2          #+#    #+#             */
/*   Updated: 2022/10/16 19:38:05 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*

Checks whether c is a 7-bit unsigned char value that fits into the ASCII
character set.

*/

int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}
