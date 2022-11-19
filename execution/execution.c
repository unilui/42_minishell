/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 00:36:26 by lufelip2          #+#    #+#             */
/*   Updated: 2022/11/19 15:58:58 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	wait_child(int *id)
{
	int	wstatus;

	if (id)
		waitpid(*id, NULL, 0);
	else
	{
		while (wait(&wstatus) > 0)
			g_data.last_exit_code = WEXITSTATUS(wstatus);
	}
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

void	wait_handler(t_cmd *cmd, int last_type, int *last_id, int *force_wait)
{
	int	i;

	if (cmd->type == EXT_BUILT_IN)
	{
		i = 0;
		while (i++ < 5000000)
			continue ;
	}
	if ((last_type == EXT_BUILT_IN && !ft_strcmp(cmd->name, "heredoc"))
		|| *force_wait)
	{
		wait_child(last_id);
		*force_wait = 0;
	}
}

void	child_process(t_cmd *cmd)
{
	static int	last_type;
	static int	last_id;
	static int	force_wait;

	pipe_handler(SWAP);
	wait_handler(cmd, last_type, &last_id, &force_wait);
	if (!ft_strcmp(cmd->name, "heredoc"))
		force_wait = 1;
	last_id = fork();
	if (!last_id)
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
		force_wait = 0;
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
