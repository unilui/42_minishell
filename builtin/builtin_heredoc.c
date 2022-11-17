/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 07:31:18 by lufelip2          #+#    #+#             */
/*   Updated: 2022/11/08 08:47:45 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	builtin_heredoc(char **args)
{
	char	*line;
	char	**table;
	char	**tmp;

	table = NULL;
	line = readline("> ");
	while (ft_strcmp(line, args[1]))
	{
		tmp = table;
		if (*line)
		{
			g_data.line = line;
			var_expand();
			line = g_data.line;
		}
		table = buffer_table(table, line);
		if (tmp)
			free(tmp);
		line = readline("> ");
	}
	send_buffer(table, g_data.pipe_out[1], TRUE);
	free_table(table);
	g_data.line = NULL;
	free(line);
	g_data.last_exit_code = 0;
}
