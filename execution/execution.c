/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 00:36:26 by lufelip2          #+#    #+#             */
/*   Updated: 2022/11/17 21:59:30 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	wait_child(int *status)
{
	int	wstatus;

	while (wait(&wstatus) > 0)
		g_data.last_exit_code = WEXITSTATUS(wstatus);
	if (status)
		*status = 0;
}

void	exec_builtin(t_cmd *cmd)
{
	if (!ft_strcmp(cmd->name, "heredoc"))
		builtin_heredoc(cmd->args);
	else if (!ft_strcmp(cmd->name, "infile"))
		builtin_infile(cmd->args);
	else if (!ft_strcmp(cmd->name, "append"))
		builtin_write(cmd->args);
	else if (!ft_strcmp(cmd->name, "overwrite"))
		builtin_write(cmd->args);
	else if (!ft_strcmp(cmd->name, "exit"))
		builtin_exit(cmd->args);
	else if (!ft_strcmp(cmd->name, "env"))
		builtin_env(g_data.extern_env, FALSE);
	else if (!ft_strcmp(cmd->name, "echo"))
		builtin_echo(cmd->args);
	else if (!ft_strcmp(cmd->name, "pwd"))
		builtin_pwd();
	else if (!ft_strcmp(cmd->name, "cd"))
		builtin_cd(cmd->args);
	else if (!ft_strcmp(cmd->name, "export"))
		builtin_export(cmd->args);
	else if (!ft_strcmp(cmd->name, "unset"))
		builtin_unset(cmd->args);
	else
		builtin_import(cmd->args);
}

void	wait_handler(t_cmd *cmd, int *wait_builtin, int last_type)
{
	if (*wait_builtin && cmd->type == EXT_BUILT_IN)
		wait_child(wait_builtin);
	if (cmd->type == EXT_BUILT_IN
		&& last_type == EXT_BUILT_IN
		&& cmd->next
		&& cmd->next->type == EXTERNAL)
		*wait_builtin = 1;
}

void	child_process(t_cmd *cmd)
{
	static int	wait_builtin;
	static int	last_type;

	pipe_handler(SWAP);
	wait_handler(cmd, &wait_builtin, last_type);
	if (!fork())
	{
		sig_defaults();
		set_child_pipes(cmd);
		if (cmd->type != EXTERNAL)
		{
			exec_builtin(cmd);
			exit_shell(0);
		}
		else
			execve(cmd->name, cmd->args, g_data.env_table);
	}
	pipe_handler(CLOSE_IN);
	last_type = cmd->type;
	if (!cmd->next)
		wait_builtin = 0;
}

void	execution(void)
{
	t_cmd	*cmd;

	cmd = g_data.cmd;
	if (!cmd)
		return ;
	ignore_signals();
	while (cmd)
	{
		if (cmd->type == BUILT_IN)
			exec_builtin(cmd);
		else if (cmd->type == EXTERNAL)
		{
			if (path_expand(cmd))
				child_process(cmd);
		}
		else
			child_process(cmd);
		cmd = cmd->next;
	}
	pipe_handler(CLOSE_INIT);
	pipe_handler(CLOSE_OUT);
	wait_child(NULL);
	clear_exec_lst(&g_data.cmd);
	signal_handlers();
}
