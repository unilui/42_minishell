/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_nearby_ops.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 02:40:12 by lufelip2          #+#    #+#             */
/*   Updated: 2022/11/08 05:40:14 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	skip_colapses(int *prev_op, int *next_op, int *op, int *clp)
{
	int	i;

	i = 0;
	while (i <= *clp)
	{
		*prev_op = *next_op;
		*op = next_operator(g_data.line, next_op);
		i++;
	}
}

void	get_nearby_ops(int *prev_op, int *next_op)
{
	static int	init;
	static int	clp;
	int			op;

	if (!init)
	{
		if (is_operator(0, g_data.line))
			next_operator(g_data.line, prev_op);
		else
			*prev_op = 0;
		op = next_operator(g_data.line, next_op);
		if (op)
			init++;
		if (op == 6)
			clp++;
		return ;
	}
	skip_colapses(prev_op, next_op, &op, &clp);
	if (!op)
		init = 0;
	if (op != 6)
		clp = 0;
}
