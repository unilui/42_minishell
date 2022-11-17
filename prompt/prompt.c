/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 21:09:10 by lufelip2          #+#    #+#             */
/*   Updated: 2022/11/12 21:33:51 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	history_handler(void)
{
	if (!g_data.old_line)
	{
		g_data.old_line = ft_strdup(g_data.line);
		add_history(g_data.line);
	}
	if (ft_strcmp(g_data.old_line, g_data.line))
	{
		add_history(g_data.line);
		free(g_data.old_line);
		g_data.old_line = ft_strdup(g_data.line);
	}
}

int	open_pipe_check(void)
{
	int	i;

	i = ft_strlen(g_data.line) - 1;
	while (i > 0 && g_data.line[i] == ' ')
		i--;
	if (i > 0
		&& g_data.line[i] == '|'
		&& g_data.line[i - 1] != '|')
		return (1);
	return (0);
}

void	read_missing_command(void)
{
	char	*tmp;
	char	*new_line;

	new_line = readline("pipe > ");
	if (*new_line)
	{
		tmp = g_data.line;
		g_data.line = ft_strjoin(tmp, " ");
		free(tmp);
		tmp = new_line;
		new_line = ft_strtrim(new_line, " ");
		free(tmp);
		tmp = g_data.line;
		g_data.line = ft_strjoin(tmp, new_line);
		free(tmp);
	}
	free(new_line);
}

void	get_new_line(void)
{
	char	*tmp;

	if (g_data.shell_init)
	{
		g_data.line = ft_strdup("clear");
		g_data.shell_init = FALSE;
		return ;
	}
	if (!g_data.last_exit_code)
		g_data.line = readline(GREEN"❯ "RESET);
	else
		g_data.line = readline(RED"❯ "RESET);
	tmp = g_data.line;
	if (tmp)
	{
		g_data.line = ft_strtrim(tmp, " ");
		free(tmp);
	}
}

void	prompt(void)
{
	print_cwd();
	get_new_line();
	if (!g_data.line)
	{
		ft_printf("\nexit\n");
		exit_shell(130);
	}
	if (*g_data.line)
	{
		while (open_pipe_check())
			read_missing_command();
		history_handler();
	}
	else
	{
		free(g_data.line);
		g_data.line = NULL;
	}
}
