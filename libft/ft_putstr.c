/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 20:43:45 by lufelip2          #+#    #+#             */
/*   Updated: 2022/10/16 19:40:25 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*

Outputs a string to the standard output.

*/

int	ft_putstr(char *str)
{
	if (str)
		return (write(1, str, ft_strlen(str)));
	return (0);
}
