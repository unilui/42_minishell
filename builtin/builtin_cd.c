/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 21:30:39 by lufelip2          #+#    #+#             */
/*   Updated: 2022/11/08 09:59:53 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static void	cd_to_path(char *new_wd)
{
	char	current_path[4096];

	getcwd(current_path, 4095);
	if (!access(new_wd, R_OK | F_OK))
	{
		if (chdir(new_wd))
		{
			ft_printf("cd: something is wrong\n");
			g_data.last_exit_code = 2;
		}
		else
		{
			set_extern_env("OLDPWD", current_path, TRUE);
			set_extern_env("PWD", getcwd(current_path, 4095), TRUE);
			g_data.last_exit_code = 0;
		}
	}
	else
	{
		ft_printf("cd: no such file or directory: %s\n", new_wd);
		g_data.last_exit_code = 1;
	}
}

void	builtin_cd(char **args)
{
	char	*new_wd;
	int		args_nbr;

	args_nbr = table_size(args);
	if (args_nbr > 2)
	{
		ft_printf("cd: Too many arguments\n");
		g_data.last_exit_code = 3;
		return ;
	}
	if (args_nbr == 1)
		new_wd = g_data.home;
	else if (!ft_strcmp(args[1], "-"))
	{
		new_wd = get_env("OLDPWD");
		if (!new_wd)
		{
			ft_printf("cd: can't go back to where you haven't been\n");
			g_data.last_exit_code = 4;
			return ;
		}
	}
	else
		new_wd = args[1];
	cd_to_path(new_wd);
}
