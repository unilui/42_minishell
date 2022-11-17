/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_spaces.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 02:15:12 by lufelip2          #+#    #+#             */
/*   Updated: 2022/10/17 00:29:15 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

char	**trim_spaces(char **table)
{
	char	*tmp;
	int		i;

	i = 0;
	while (table[i])
	{
		tmp = table[i];
		table[i] = ft_strtrim(tmp, " ");
		free(tmp);
		i++;
	}
	return (table);
}
