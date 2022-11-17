/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 20:10:23 by lufelip2          #+#    #+#             */
/*   Updated: 2022/11/13 19:55:24 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator(int position, char const *line)
{
	if (line[position] == '|'
		|| line[position] == '>'
		|| line[position] == '<')
		return (!btw_quotes(position, line));
	return (0);
}

int	is_space(int position, char const *line)
{
	if (line[position] == ' ')
		return (!btw_quotes(position, line));
	return (0);
}

int	is_var(int position, char const *line)
{
	if (line[position] == '\"'
		|| (line[position] == '$' && is_valid_identifier(&line[position])))
		return (1);
	return (0);
}

int	is_value(int position, char const *line)
{
	if (line[position] == '=')
	{
		position--;
		while (position >= 0)
		{
			if (line[position] == '=')
				return (0);
			position--;
		}
		return (1);
	}
	return (0);
}

int	is_not_operator(int position, char const *line)
{
	return (!is_operator(position, line));
}
