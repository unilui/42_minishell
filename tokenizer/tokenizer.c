/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 02:35:55 by lufelip2          #+#    #+#             */
/*   Updated: 2022/11/08 09:19:53 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	get_tokens(char **table)
{
	int		token;
	int		prev_op;
	int		next_op;
	int		b_wall;

	token = 0;
	b_wall = 0;
	while (table[token])
	{
		get_nearby_ops(&prev_op, &next_op);
		if (*table[token])
		{
			b_wall = block_direct_call(table[token]);
			if (is_local_var(table[token]))
				import_tokenizer(table[token], prev_op, next_op);
			else if (prev_op == PIPE || !prev_op || b_wall)
				exec_lst_add(&g_data.cmd,
					new_exec_token(table[token], prev_op, next_op, b_wall));
			else if (prev_op == HEREDOC || prev_op == INFILE)
				read_tokenizer(table[token], prev_op, next_op);
			else
				write_tokenizer(table[token], prev_op, next_op);
		}
		token++;
	}
}

void	tokenizer(void)
{
	char	**table;

	if (!g_data.line)
		return ;
	table = token_split(g_data.line, is_operator);
	table = trim_spaces(table);
	get_tokens(table);
	free_table(table);
	free(g_data.line);
	g_data.line = NULL;
}
