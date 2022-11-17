/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 01:39:08 by lufelip2          #+#    #+#             */
/*   Updated: 2022/11/12 14:21:36 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	exit_shell(int exit_code)
{
	clear_exec_lst(&g_data.cmd);
	clear_env_lst(&g_data.extern_env);
	clear_env_lst(&g_data.local_env);
	free_table(g_data.path);
	if (g_data.old_line)
		free(g_data.old_line);
	exit(exit_code);
}

static int	args_check(char **args)
{
	int	size;
	int	i;

	i = 0;
	size = table_size(args);
	if (size > 2)
	{
		ft_printf("exit: too many arguments\n");
		return (0);
	}
	if (size == 2)
	{
		while (args[1][i])
		{
			if (!ft_isdigit(args[1][i])
				&& args[1][i] != '-'
				&& args[1][i] != '+')
			{
				ft_printf("exit: numeric argument required\n");
				return (0);
			}
			i++;
		}
	}
	return (1);
}

void	builtin_exit(char **args)
{
	int	exit_code;

	exit_code = 0;
	if (!args_check(args))
		return ;
	if (table_size(args) == 2)
		exit_code = ft_atoi(args[1]);
	ft_printf("exit\n");
	clear_exec_lst(&g_data.cmd);
	clear_env_lst(&g_data.extern_env);
	clear_env_lst(&g_data.local_env);
	free_table(g_data.path);
	if (g_data.old_line)
		free(g_data.old_line);
	exit(exit_code);
}
