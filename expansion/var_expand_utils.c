/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expand_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 21:50:19 by lufelip2          #+#    #+#             */
/*   Updated: 2022/11/17 19:39:29 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	btw_double_quotes(int position, char *str)
{
	int	i;
	int	before_quotes;
	int	after_quotes;

	i = position;
	before_quotes = 0;
	after_quotes = 0;
	while (i >= 0)
	{
		if (str[i] == '\"')
			before_quotes = 1;
		if (str[i] == '\'')
			before_quotes = 0;
		i--;
	}
	i = position;
	while (str[i])
	{
		if (str[i] == '\"')
			after_quotes = 1;
		if (str[i] == '\'')
			after_quotes = 0;
		i++;
	}
	return (before_quotes && after_quotes);
}

int	btw_single_quotes(char *str)
{
	int	i;
	int	x;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			return (0);
		if (str[i] == '\'')
			break ;
		i++;
	}
	x = ft_strlen(str) - 1;
	while (x >= 0)
	{
		if (str[x] == '\"')
			return (0);
		if (str[x] == '\'')
			break ;
		x--;
	}
	return (i < x);
}

int	is_valid_identifier(char const *chr)
{
	char	chr_i;

	chr_i = *(chr + 1);
	if (ft_isalnum(chr_i) || chr_i == '?' || chr_i == '~')
		return (1);
	return (0);
}

int	is_expandable(char *str)
{
	char	*dollar_sign;

	dollar_sign = ft_strchr(str, '$');
	if (dollar_sign && is_valid_identifier(dollar_sign))
		return (btw_double_quotes((dollar_sign - str), str)
			&& !btw_single_quotes(str));
	return (0);
}

void	trim_quotes(char **var)
{
	char	**split_line;

	if (btw_single_quotes(*var))
		split_line = ft_split(*var, '\'');
	else
		split_line = ft_split(*var, '\"');
	free(*var);
	*var = table_join(split_line, "");
	free_table(split_line);
}
