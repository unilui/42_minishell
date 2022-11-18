/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expand_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 19:35:00 by lufelip2          #+#    #+#             */
/*   Updated: 2022/11/17 21:55:57 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

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
	char	*tmp;

	tmp = *var;
	*var = ft_strjoin("\"", *var);
	free(tmp);
	tmp = *var;
	*var = ft_strjoin(*var, "\"");
	free(tmp);
}

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

void	replace_home(char **var)
{
	char	*tmp;

	if (ft_strlen(*var) > 1)
	{
		tmp = ft_strjoin(g_data.home, *var + 1);
		free(*var);
		*var = tmp;
	}
	else
	{
		free(*var);
		*var = ft_strdup(g_data.home);
	}
}

void	expand_handler(char **tokens)
{
	int	i;

	i = 0;
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
}
