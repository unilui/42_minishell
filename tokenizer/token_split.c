/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 20:19:37 by lufelip2          #+#    #+#             */
/*   Updated: 2022/11/13 20:03:12 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	token_count(char const *line, int (*is_sep)(int, char const *))
{
	int	tokens;
	int	i;

	tokens = 1;
	i = 0;
	while (line[i] && is_sep(i, line))
		i++;
	while (line[i])
	{
		if (is_sep(i, line) && !is_sep((i + 1), line) && line[i + 1])
			tokens++;
		i++;
	}
	return (tokens);
}

static char	*create_token(int offset, int letters, char const *line)
{
	int		reverse;
	char	*token;

	reverse = 1;
	token = malloc(letters + 1);
	if (!token)
		return (NULL);
	token[letters--] = '\0';
	while (letters >= 0)
		token[letters--] = line[offset - reverse++];
	return (token);
}

static char	*new_token(char const *line, int (*is_sep)(int, char const *))
{
	static int	offset;
	int			letters;
	char		*token;

	letters = 0;
	while (line[offset] && is_sep(offset, line))
		offset++;
	while (!is_sep(offset, line) && line[offset])
	{
		letters++;
		offset++;
	}
	token = create_token(offset, letters, line);
	while (line[offset] && is_sep(offset, line))
		offset++;
	if (!line[offset])
		offset = 0;
	return (token);
}

char	**token_split(char const *line, int (*is_sep)(int, char const *))
{
	char	**token_table;
	int		tokens;
	int		i;

	i = 0;
	tokens = token_count(line, is_sep);
	token_table = malloc((tokens + 1) * sizeof(char *));
	if (!token_table)
		return (NULL);
	while (i < tokens)
		token_table[i++] = new_token(line, is_sep);
	token_table[i] = NULL;
	return (token_table);
}
