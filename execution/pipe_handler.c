/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 19:10:52 by lufelip2          #+#    #+#             */
/*   Updated: 2022/11/17 21:59:35 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_handler(int op)
{
	static int	init;
	static int	hist;

	if (op == SWAP)
		pipe_swap(&init);
	else if (op == CLOSE_IN)
		pipe_close_in(&hist);
	else if (op == CIRCLE_PIPE)
		pipe_circle(hist);
	else if (op == CLOSE_INIT)
		pipe_close_init(hist);
	else if (op == CLOSE_OUT)
		pipe_close_out(&init, &hist);
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
