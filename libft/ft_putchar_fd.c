/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 19:32:25 by lufelip2          #+#    #+#             */
/*   Updated: 2022/10/16 19:39:42 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*

Outputs the character ’c’ to the given file descriptor (fd).

*/

void	ft_putchar_fd(char c, int fd)
{
	write (fd, &c, 1);
}
