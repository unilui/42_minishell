/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 03:32:52 by lufelip2          #+#    #+#             */
/*   Updated: 2022/11/11 11:12:14 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	replace_exit_code(char **str)
{
	char	*tmp;
	char	*tmp_i;

	tmp = ft_itoa(g_data.last_exit_code);
	tmp_i = *str;
	*str = ft_strjoin(tmp, *str + 1);
	free(tmp);
	free(tmp_i);
}

void	replace_var(char **str)
{
	char	*tmp;

	tmp = get_env(*str);
	if (tmp)
	{
		free(*str);
		*str = ft_strdup(tmp);
	}
	else if (!tmp && !ft_strcmp(*str, "?"))
	{
		free(*str);
		*str = ft_itoa(g_data.last_exit_code);
	}
	else if (!tmp && *str[0] == '?')
		replace_exit_code(str);
	else
	{
		free(*str);
		*str = ft_strdup("\0");
	}
}

void	expand_var(char **var)
{
	int		i;
	char	*position;
	char	**split_line;

	i = 0;
	if (!ft_strcmp(*var, "$"))
		return ;
	split_line = ft_split(*var, '$');
	while (split_line[i])
	{
		position = ft_strnstr(*var, split_line[i], ft_strlen(*var));
		if (position != *var && *(position - 1) == '$')
			replace_var(&split_line[i]);
		i++;
	}
	free(*var);
	*var = table_join(split_line, "");
	free_table(split_line);
}

void	replace_var_str(char **str, int position)
{
	char	*tmp;
	char	*tmp_i;

	tmp = ft_substr(*str, 0, position);
	tmp_i = ft_strdup(get_env(tmp));
	if (!tmp_i && *str[0] == '?')
		tmp_i = ft_itoa(g_data.last_exit_code);
	else if (!tmp_i)
		tmp_i = ft_strdup("\0");
	free(tmp);
	tmp = ft_substr(*str, position, ft_strlen(*str));
	free(*str);
	*str = ft_strjoin(tmp_i, tmp);
	free(tmp);
	free(tmp_i);
}

void	expand_str(char **var)
{
	int		i;
	int		x;
	char	*position;
	char	**split_line;

	i = 0;
	split_line = token_split(*var, is_var);
	while (split_line[i])
	{
		x = 0;
		position = ft_strnstr(*var, split_line[i], ft_strlen(*var));
		if (position != *var && *(position - 1) == '$')
		{
			while (split_line[i][x] != ' '
				&& split_line[i][x] != '\''
				&& split_line[i][x])
				x++;
			replace_var_str(&split_line[i], x);
		}
		i++;
	}
	free(*var);
	*var = table_join(split_line, "");
	free_table(split_line);
}

int	no_quotes(char *var)
{
	int	len;

	len = ft_strlen(var);
	if (var[0] == '\'' || var[len] == '\'')
		return (0);
	if (var[0] == '\"' || var[len] == '\"')
		return (0);
	return (1);
}

void	put_quotes(char **var)
{
	char *tmp;

	tmp = *var;
	*var = ft_strjoin("\"", *var);
	free(tmp);
	tmp = *var;
	*var = ft_strjoin(*var, "\"");
	free(tmp);
}

void	var_expand(void)
{
	int		i;
	char	**tokens;

	if (!g_data.line)
		return ;
	i = 0;
	tokens = token_split(g_data.line, is_space);
	while (tokens[i])
	{
		if (tokens[i][0] == '~' && !ft_strchr(tokens[i], '$'))
			replace_home(&tokens[i]);
		else if (ft_strchr(tokens[i], '$') && no_quotes(tokens[i]))
			expand_var(&tokens[i]);
		else
		{
			if (is_expandable(tokens[i]))
			{
				expand_str(&tokens[i]);
				if (ft_strchr(tokens[i], ' '))
					put_quotes(&tokens[i]);
			}
		}
		i++;
	}
	free(g_data.line);
	g_data.line = table_join(tokens, " ");
	free_table(tokens);
}
