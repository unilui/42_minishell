/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_exec_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 00:23:48 by lufelip2          #+#    #+#             */
/*   Updated: 2022/11/07 21:54:33 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	set_exec_path(void)
{
	char	**path_table;
	char	*path_env;
	int		i;

	if (g_data.path)
		free_table(g_data.path);
	path_env = get_env("PATH");
	if (path_env)
		path_table = ft_split(get_env("PATH"), ':');
	else
		path_table = NULL;
	g_data.path = malloc((table_size(path_table) + 2) * sizeof(char *));
	i = -1;
	while (path_table && path_table[++i])
		g_data.path[i] = ft_strjoin(path_table[i], "/");
	if (!path_env)
		++i;
	g_data.path[i] = ft_strdup("");
	g_data.path[++i] = NULL;
	if (path_table)
		free_table(path_table);
}
