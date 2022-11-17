/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   placeholder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 17:43:43 by lufelip2          #+#    #+#             */
/*   Updated: 2022/10/16 19:46:59 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

/*

Returns a function that replaces the given character 'placeholder'.

*/

t_replace	placeholder(char placeholder)
{
	if (placeholder == 'c')
		return (replace_chr);
	if (placeholder == 'd'
		|| placeholder == 'i')
		return (replace_int);
	if (placeholder == 's')
		return (replace_str);
	if (placeholder == 'u')
		return (replace_uint);
	if (placeholder == 'x'
		|| placeholder == 'X')
		return (replace_hexa);
	if (placeholder == 'p')
		return (replace_ptr);
	return (skip_replace);
}
