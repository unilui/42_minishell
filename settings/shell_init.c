/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 19:28:11 by lufelip2          #+#    #+#             */
/*   Updated: 2022/11/12 16:49:11 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	request_home(void)
{
	ft_printf("\033c");
	ft_printf("Minishell: please, set your home path :)\n");
	ft_printf("Just type, like: /your/home/path\n");
	while (access(g_data.home, R_OK | F_OK))
	{
		g_data.home = readline(GREEN"❯ "RESET);
		if (!access(g_data.home, R_OK | F_OK))
			break ;
		else
		{
			ft_printf("Minishell: no such file or directory\n");
			free(g_data.home);
		}
	}
	set_extern_env("HOME", g_data.home, TRUE);
}

void	shell_init(char **envp)
{
	ft_memset(&g_data, 0, sizeof(t_data));
	set_env_variables(envp, &g_data.extern_env);
	g_data.shell_init = TRUE;
	g_data.home = get_env("HOME");
	if (!g_data.home)
		request_home();
	set_env_table();
	set_exec_path();
	signal_handlers();
}
