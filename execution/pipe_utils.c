/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 00:44:37 by lufelip2          #+#    #+#             */
/*   Updated: 2022/10/30 00:30:25 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_swap(int *init)
{
	if (!*init)
	{
		pipe(g_data.pipe_out);
		*init = 1;
	}
	g_data.pipe_in[0] = g_data.pipe_out[0];
	g_data.pipe_in[1] = g_data.pipe_out[1];
	pipe(g_data.pipe_out);
}

void	pipe_close_in(int *hist)
{
	if (!*hist)
	{
		g_data.init_pipe_in[0] = g_data.pipe_in[0];
		g_data.init_pipe_in[1] = g_data.pipe_in[1];
		*hist = 1;
		return ;
	}
	close(g_data.pipe_in[0]);
	close(g_data.pipe_in[1]);
}

void	pipe_circle(int hist)
{
	if (hist)
	{
		close(g_data.pipe_out[0]);
		close(g_data.pipe_out[1]);
		g_data.pipe_out[0] = g_data.init_pipe_in[0];
		g_data.pipe_out[1] = g_data.init_pipe_in[1];
	}
}

void	pipe_close_init(int hist)
{
	if (hist)
	{
		close(g_data.init_pipe_in[0]);
		close(g_data.init_pipe_in[1]);
	}
}

void	pipe_close_out(int *init, int *hist)
{
	if (init)
	{
		close(g_data.pipe_out[0]);
		close(g_data.pipe_out[1]);
	}
	*init = 0;
	*hist = 0;
}
