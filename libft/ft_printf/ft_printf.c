/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 17:30:47 by lufelip2          #+#    #+#             */
/*   Updated: 2022/10/16 19:46:22 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

/*

Formats and prints its arguments, after the first, under control of the
format.  The format is a character string which contains two types of objects:
plain characters, which are simply copied to standard output and character
escape sequences which are converted and copied to the standard output, each of
which causes printing of the next successive argument.

*/

int	ft_printf(const char *str, ...)
{
	t_str	str_args;

	va_start(str_args.args, str);
	str_args.written = 0;
	if (str)
	{
		while (*str)
		{
			str_args.chr = *str;
			replace_handler(&str_args);
			str++;
		}
	}
	va_end(str_args.args);
	return (str_args.written);
}
