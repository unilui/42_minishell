/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 19:34:00 by lufelip2          #+#    #+#             */
/*   Updated: 2022/11/08 21:46:04 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	is_executable(char **name)
{
	char	*path;

	path = get_path(*name);
	if (!path)
	{
		g_data.last_exit_code = 126;
		return (0);
	}
	free(*name);
	*name = path;
	return (1);
}

int	is_directory(char *path)
{
	struct stat	sb;

	if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode))
	{
		g_data.last_exit_code = 126;
		return (1);
	}
	return (0);
}

int	path_expand(t_cmd *cmd)
{
	if (!is_executable(&cmd->name))
	{
		wait_child(NULL);
		ft_printf("command not found: %s\n", cmd->name);
		return (0);
	}
	if (is_directory(cmd->name))
	{
		wait_child(NULL);
		ft_printf("Is a directory: %s\n", cmd->name);
		return (0);
	}
	return (1);
}
