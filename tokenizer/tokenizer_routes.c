/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_routes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 09:19:33 by lufelip2          #+#    #+#             */
/*   Updated: 2022/11/19 13:05:35 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	arg_hoisting(char *args)
{
	t_cmd	*tmp_cmd;
	char	*args_tmp;
	char	*tmp;

	tmp_cmd = g_data.cmd;
	while (tmp_cmd)
	{
		if (!tmp_cmd->write_op
			&& (!tmp_cmd->next || (tmp_cmd->next)->write_op))
		{
			args_tmp = table_join(tmp_cmd->args, " ");
			tmp = args_tmp;
			args_tmp = ft_strjoin(tmp, " ");
			free(tmp);
			tmp = args_tmp;
			args_tmp = ft_strjoin(tmp, args);
			free(tmp);
			free_table(tmp_cmd->args);
			tmp_cmd->args = token_split(args_tmp, is_space);
			free(args_tmp);
			break ;
		}
		else
			tmp_cmd = tmp_cmd->next;
	}
}

void	write_tokenizer(char *cmd, int prev_op)
{
	char	*new_cmd;
	char	*tmp;
	char	**args;

	if (prev_op == APPEND)
		new_cmd = ft_strjoin("append ", cmd);
	else
		new_cmd = ft_strjoin("overwrite ", cmd);
	args = token_split(new_cmd, is_space);
	if (table_size(args) > 2)
	{
		tmp = table_join((args + 2), " ");
		arg_hoisting(tmp);
		free(tmp);
	}
	exec_lst_add(&g_data.cmd, new_exec_token(new_cmd, prev_op, FALSE, FALSE));
	free(new_cmd);
	free_table(args);
}

void	read_tokenizer(char *cmd, int prev_op, int next_op)
{
	char	*tmp;
	char	*new_cmd;
	char	**args;

	if (prev_op == HEREDOC)
		new_cmd = ft_strjoin("heredoc ", cmd);
	else
		new_cmd = ft_strjoin("infile ", cmd);
	args = token_split(new_cmd, is_space);
	exec_lst_add(&g_data.cmd, new_exec_token(new_cmd, prev_op, FALSE, FALSE));
	if (table_size(args) > 2)
	{
		tmp = table_join((args + 2), " ");
		arg_hoisting(tmp);
		exec_lst_add(&g_data.cmd, new_exec_token(tmp, PIPE, next_op, FALSE));
		free(tmp);
	}
	free(new_cmd);
	free_table(args);
}

void	import_tokenizer(char *cmd, int prev_op)
{
	char	*new_cmd;
	char	**args;

	new_cmd = ft_strjoin("import ", cmd);
	args = token_split(new_cmd, is_space);
	exec_lst_add(&g_data.cmd, new_exec_token(new_cmd, prev_op, FALSE, FALSE));
	free(new_cmd);
	free_table(args);
}

int	is_local_var(char *cmd)
{
	char	*chr;

	chr = ft_strchr(cmd, '=');
	if (chr
		&& *cmd != '='
		&& *(chr + 1)
		&& *(chr + 1) != '\''
		&& *(chr + 1) != '\"'
		&& !ft_strchr(cmd, ' ')
		&& !ft_strnstr(cmd, "export", ft_strlen(cmd)))
		return (1);
	return (0);
}
