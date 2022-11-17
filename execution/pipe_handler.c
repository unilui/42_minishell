/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 19:10:52 by lufelip2          #+#    #+#             */
/*   Updated: 2022/10/30 00:29:58 by lufelip2         ###   ########.fr       */
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
