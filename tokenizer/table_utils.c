/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 00:51:09 by lufelip2          #+#    #+#             */
/*   Updated: 2022/11/08 01:34:38 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	table_size(char **table)
{
	int		i;

	i = 0;
	if (!table)
		return (i);
	while (*table++)
		i++;
	return (i);
}

char	*table_join(char **table, char *sep)
{
	int		i;
	char	*str;
	char	*tmp;
	char	*tmp_str;

	i = 0;
	tmp = NULL;
	str = NULL;
	tmp_str = NULL;
	while (table[i])
	{
		tmp_str = str;
		if (table[i + 1] && *sep)
		{
			tmp = ft_strjoin(table[i], sep);
			str = ft_strjoin(str, tmp);
			free(tmp);
		}
		else
			str = ft_strjoin(str, table[i]);
		free(tmp_str);
		i++;
	}
	return (str);
}
