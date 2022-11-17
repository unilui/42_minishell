/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 23:12:56 by lufelip2          #+#    #+#             */
/*   Updated: 2022/11/08 08:46:42 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	builtin_echo(char **args)
{
	int		new_line;
	char	*text;
	int		i;

	new_line = 1;
	i = 1;
	if (table_size(args) > 1 && !ft_strcmp(args[1], "-n"))
	{
		new_line--;
		i++;
	}
	if (table_size(args) > 1)
	{
		text = table_join((args + i), " ");
		ft_printf("%s", text);
		free(text);
	}
	if (new_line)
		ft_printf("\n");
	g_data.last_exit_code = 0;
}
