/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 00:36:26 by lufelip2          #+#    #+#             */
/*   Updated: 2022/11/12 22:42:01 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"


void	print_token(t_cmd *cmd)
{
	int	i;

	i = 1;
	ft_printf("Command name: %s\n", cmd->name);
	while (cmd->args[i])
	{
		ft_printf("Argument %d: %s\n", i, cmd->args[i]);
		i++;
	}
	ft_printf("Pipe in: %d\n", cmd->pipe_in);
	ft_printf("Pipe out: %d\n", cmd->pipe_out);
	if (cmd->type == 1)
		ft_printf("Type: EXTERNAL\n");
	else if (cmd->type == 2)
		ft_printf("Type: BUILT_IN\n");
	else if (cmd->type == 3)
		ft_printf("Type: EXT_BUILT_IN\n");
	ft_printf("=======================================\n");
}


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

void	set_child_pipes(t_cmd *cmd)
{
	int	fd;

	if (cmd->next)
		pipe_handler(CLOSE_INIT);
	else
		pipe_handler(CIRCLE_PIPE);
	close(g_data.pipe_in[1]);
	if ((cmd->type == EXTERNAL && cmd->next) || cmd->pipe_in)
	{
		fd = dup(g_data.pipe_in[0]);
		dup2(fd, STDIN_FILENO);
	}
	close(g_data.pipe_out[0]);
	if (cmd->pipe_out)
	{
		fd = dup(g_data.pipe_out[1]);
		dup2(fd, STDOUT_FILENO);
	}
}

void	child_process(t_cmd *cmd)
{
	static int	wait_builtin;
	static int	last_type;

	pipe_handler(SWAP);
	if (wait_builtin && cmd->type == EXT_BUILT_IN)
	{
		printf("%s->%s\n", cmd->name, cmd->args[1]);
		wait_child(&wait_builtin);
	}
	if (cmd->type == EXT_BUILT_IN
		&& last_type == EXT_BUILT_IN
		&& cmd->next
		&& cmd->next->type == EXTERNAL)
		wait_builtin = 1;
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
