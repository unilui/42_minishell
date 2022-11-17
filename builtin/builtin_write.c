/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_write.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:54:27 by lufelip2          #+#    #+#             */
/*   Updated: 2022/11/13 13:47:28 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static void	write_to_fd(int fd)
{
	char	*line;
	char	**table;
	char	**tmp;
	int		i;

	i = 0;
	table = NULL;
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		tmp = table;
		table = buffer_table(table, line);
		if (tmp)
			free(tmp);
		ft_putstr_fd(line, fd);
		line = get_next_line(STDIN_FILENO);
	}
	send_buffer(table, g_data.pipe_out[1], FALSE);
	free_table(table);
	g_data.last_exit_code = 0;
}

void	builtin_write(char **args)
{
	int		fd;

	if (!ft_strcmp(args[0], "append"))
		fd = open(args[1], O_WRONLY | O_CREAT | O_APPEND, S_IRWXU);
	else
		fd = open(args[1], O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	if (fd < 0)
	{
		if (is_directory(args[1]))
			ft_printf("Is a directory: %s\n", args[1]);
		else
			ft_printf("No such file or directory: %s\n", args[1]);
		g_data.last_exit_code = 1;
		return ;
	}
	write_to_fd(fd);
	close(fd);
}
