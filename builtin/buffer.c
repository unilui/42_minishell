/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 21:48:05 by lufelip2          #+#    #+#             */
/*   Updated: 2022/10/26 21:48:25 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

char	**buffer_table(char **table, char *str)
{
	char	**new_table;
	int		i;

	i = 0;
	new_table = malloc((table_size(table) + 2) * sizeof(char *));
	if (!new_table)
		return (NULL);
	while (table && table[i])
	{
		new_table[i] = table[i];
		i++;
	}
	new_table[i] = str;
	new_table[++i] = NULL;
	return (new_table);
}

void	send_buffer(char **table, int fd, int nwl)
{
	int	i;

	i = 0;
	while (table && table[i])
	{
		ft_putstr_fd(table[i], fd);
		if (nwl)
			ft_putstr_fd("\n", fd);
		i++;
	}
}
