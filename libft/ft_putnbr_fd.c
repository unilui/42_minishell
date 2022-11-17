/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 19:52:33 by lufelip2          #+#    #+#             */
/*   Updated: 2022/10/16 19:40:04 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*

Outputs the integer ’n’ to the given file descriptor (fd).

*/

void	ft_putnbr_fd(int n, int fd)
{
	if (n < -9 || n > 9)
		ft_putnbr_fd((n / 10), fd);
	if (n >= -9 && n < 0)
		ft_putchar_fd('-', fd);
	if (n < 0)
		ft_putchar_fd((-(n % 10) + '0'), fd);
	else
		ft_putchar_fd(((n % 10) + '0'), fd);
}
