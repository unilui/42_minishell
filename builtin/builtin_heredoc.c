/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 07:31:18 by lufelip2          #+#    #+#             */
/*   Updated: 2022/11/19 14:22:22 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	i_hate_u_norme(char **table)
{
	if (table)
		send_buffer(table, g_data.pipe_out[1], TRUE);
	if (table)
		free_table(table);
}

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
	i_hate_u_norme(table);
	g_data.line = NULL;
	free(line);
	g_data.last_exit_code = 0;
}
