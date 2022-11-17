/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_infile.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 09:07:45 by lufelip2          #+#    #+#             */
/*   Updated: 2022/11/08 20:38:07 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	builtin_infile(char **args)
{
	int		fd;
	char	*line;

	fd = open(args[1], O_RDONLY);
	if (fd < 0)
	{
		ft_printf("No such file or directory: %s\n", args[1]);
		g_data.last_exit_code = 1;
		return ;
	}
	line = get_next_line(fd);
	while (line)
	{
		ft_putstr_fd(line, g_data.pipe_out[1]);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	g_data.last_exit_code = 0;
}
