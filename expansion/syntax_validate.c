/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_validate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 21:17:37 by lufelip2          #+#    #+#             */
/*   Updated: 2022/11/13 21:01:23 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static int	open_quotes(void)
{
	int	single_quotes;
	int	double_quotes;
	int	i;

	i = 0;
	single_quotes = 0;
	double_quotes = 0;
	while (g_data.line[i])
	{
		if (g_data.line[i] == '\"' && !double_quotes && !single_quotes)
			double_quotes++;
		else if (g_data.line[i] == '\"' && double_quotes && !single_quotes)
			double_quotes--;
		else if (g_data.line[i] == '\'' && !single_quotes && !double_quotes)
			single_quotes++;
		else if (g_data.line[i] == '\'' && single_quotes && !double_quotes)
			single_quotes--;
		i++;
	}
	if (single_quotes || double_quotes)
	{
		ft_printf("Close your quotes :)\n");
		return (1);
	}
	return (0);
}

int	unexpected_token(void)
{
	int	len;

	if (is_operator(0, g_data.line))
	{
		ft_printf("syntax error near unexpected token: `%c'\n",
			g_data.line[0]);
		return (1);
	}
	len = ft_strlen(g_data.line) - 1;
	if (is_operator(len, g_data.line) && g_data.line[len] != '|')
	{
		ft_printf("syntax error near unexpected token: `%c'\n",
			g_data.line[len]);
		return (1);
	}
	return (0);
}

int	valid_operator(char *op)
{
	if (!ft_strcmp(op, "|")
		|| !ft_strcmp(op, ">")
		|| !ft_strcmp(op, ">>")
		|| !ft_strcmp(op, "<")
		|| !ft_strcmp(op, "<<"))
		return (1);
	return (0);
}

int wrong_op(void)
{
	char	**tokens;
	int		i;

	i = 0;
	tokens = token_split(g_data.line, is_not_operator);
	while (tokens[i])
	{
		if (*tokens[i] && !valid_operator(tokens[i]))
		{
			ft_printf("syntax error near unexpected token: `%c'\n", tokens[i][0]);
			free_table(tokens);
			return (1);
		}
		i++;
	}
	free_table(tokens);
	return (0);
}

int	sequence_op(void)
{
	char	**tokens;
	int		i;

	i = 0;
	tokens = token_split(g_data.line, is_not_operator);
	while (tokens[i])
	{
		if (*tokens[i] && valid_operator(tokens[i])
			&& tokens[i + 1] && *tokens[i + 1]
			&& valid_operator(tokens[i + 1]))
		{
			ft_printf("syntax error near unexpected token: `%c'\n", tokens[i][0]);
			free_table(tokens);
			return (1);
		}
		i++;
	}
	free_table(tokens);
	return (0);
}

void	syntax_validate(void)
{
	if (!g_data.line)
		return ;
	if (wrong_op()
		|| unexpected_token()
		|| open_quotes()
		|| sequence_op())
	{
		free(g_data.line);
		g_data.line = NULL;
	}
}