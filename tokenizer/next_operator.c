/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_operator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 02:55:17 by lufelip2          #+#    #+#             */
/*   Updated: 2022/11/08 05:29:38 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	classify_operator(int position, char *line)
{
	if (line[position] == '|')
		return (PIPE);
	else if (line[position] == '<')
	{
		if (line[position + 1] == '<')
			return (HEREDOC);
		else
			return (INFILE);
	}
	else if (line[position] == '>')
	{
		if (line[position + 1] == '>')
			return (APPEND);
		else
			return (OVERWRITE);
	}
	return (0);
}

static void	skip_operators(char *line, int *i, int *op)
{
	while (is_operator(*i, line))
	{
		if (*i > 0 && is_operator((*i - 1), line)
			&& line[*i] != line[*i - 1])
		{
			*op = 6;
			break ;
		}
		else
			*i += 1;
	}
}

int	next_operator(char *line, int *operator)
{
	static int	i;
	int			op;

	*operator = 0;
	op = 0;
	while (line[i])
	{
		if (is_operator(i, line))
		{
			*operator = classify_operator(i, line);
			op = *operator;
			i++;
			break ;
		}
		i++;
	}
	skip_operators(line, &i, &op);
	if (!line[i])
	{
		i = 0;
		return (0);
	}
	return (op);
}
