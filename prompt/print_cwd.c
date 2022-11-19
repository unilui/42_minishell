/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 05:10:34 by lufelip2          #+#    #+#             */
/*   Updated: 2022/11/19 13:37:28 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static void	put_directories(char **directories, char *path, int *printed)
{
	int		i;
	int		home_len;

	i = 0;
	home_len = ft_strlen(g_data.home);
	while (directories[i])
	{
		if (!ft_strnstr(g_data.home, directories[i], home_len)
			|| (ft_strlen(path) < home_len))
		{
			if (directories[i + 1])
				ft_printf(DARK_BLUE"/%s"RESET, directories[i]);
			else
				ft_printf(DARK_BLUE"/"LIGHT_BLUE"%s"RESET, directories[i]);
			*printed += ft_strlen(directories[i]) + 1;
		}
		i++;
	}
}

static void	put_dots(int printed)
{
	struct winsize	window;
	int				i;

	i = 0;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &window);
	ft_printf(" ");
	while (i < (window.ws_col - printed - 1))
	{
		ft_printf(GREY"·"RESET);
		i++;
	}
}

void	print_cwd(void)
{
	char	path[4096];
	char	**directories;
	int		printed;

	getcwd(path, 4095);
	directories = ft_split(path, '/');
	printed = 1;
	ft_printf("\n");
	if (ft_strnstr(path, g_data.home, ft_strlen(g_data.home)))
	{
		ft_printf(LIGHT_BLUE"~"RESET);
		printed++;
	}
	put_directories(directories, path, &printed);
	put_dots(printed);
	free_table(directories);
	ft_printf("\n");
}
