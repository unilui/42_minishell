/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 03:09:58 by lufelip2          #+#    #+#             */
/*   Updated: 2022/11/12 16:07:06 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	exec_lst_add(t_cmd **lst, t_cmd *new)
{
	t_cmd	*tmp;

	tmp = *lst;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

int	is_builtin(char *command)
{
	if (!ft_strcmp(command, "heredoc")
		|| !ft_strcmp(command, "infile")
		|| !ft_strcmp(command, "append")
		|| !ft_strcmp(command, "overwrite")
		|| !ft_strcmp(command, "echo")
		|| !ft_strcmp(command, "cd")
		|| !ft_strcmp(command, "pwd")
		|| !ft_strcmp(command, "export")
		|| !ft_strcmp(command, "unset")
		|| !ft_strcmp(command, "env")
		|| !ft_strcmp(command, "exit")
		|| !ft_strcmp(command, "import"))
		return (1);
	return (0);
}

int	block_direct_call(char *cmd)
{
	int		status;
	char	**token;

	status = 0;
	token = token_split(cmd, is_space);
	if (!ft_strcmp(token[0], "heredoc")
		|| !ft_strcmp(token[0], "infile")
		|| !ft_strcmp(token[0], "append")
		|| !ft_strcmp(token[0], "overwrite")
		|| !ft_strcmp(token[0], "import"))
		status = 1;
	free_table(token);
	return (status);
}

void	classify_token(t_cmd *cmd, int b_wall)
{
	if (is_builtin(cmd->name) && !b_wall)
	{
		if (cmd->external)
			cmd->type = EXT_BUILT_IN;
		else
			cmd->type = BUILT_IN;
	}
	else
		cmd->type = EXTERNAL;
}

t_cmd	*new_exec_token(char *cmd, int prev_op, int next_op, int b_wall)
{
	t_cmd	*token;

	token = malloc(sizeof(t_cmd));
	if (!token)
		return (NULL);
	ft_memset(token, 0, sizeof(t_cmd));
	token->args = token_split(cmd, is_space);
	token->name = ft_strdup(token->args[0]);
	if (prev_op == PIPE || prev_op == APPEND || prev_op == OVERWRITE)
		token->pipe_in++;
	if (next_op == PIPE || next_op == APPEND || next_op == OVERWRITE)
		token->pipe_out++;
	if (prev_op == OVERWRITE || prev_op == APPEND
		|| prev_op == INFILE || prev_op == HEREDOC)
		token->write_op++;
	if (prev_op || next_op)
		token->external++;
	classify_token(token, b_wall);
	return (token);
}
