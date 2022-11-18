/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 03:32:52 by lufelip2          #+#    #+#             */
/*   Updated: 2022/11/17 21:55:35 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

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

void	var_expand(void)
{
	char	**tokens;

	if (!g_data.line)
		return ;
	tokens = token_split(g_data.line, is_space);
	expand_handler(tokens);
	free(g_data.line);
	g_data.line = table_join(tokens, " ");
	free_table(tokens);
}
