/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env_variables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 00:17:15 by lufelip2          #+#    #+#             */
/*   Updated: 2022/11/08 05:45:22 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	set_env_variables(char **envp, t_env **env)
{
	char	**split_line;
	int		i;

	i = 0;
	while (envp[i])
	{
		split_line = token_split(envp[i], is_value);
		env_lst_add(env, create_var(split_line[0], split_line[1]));
		free_table(split_line);
		i++;
	}
}

void	set_env_table(void)
{
	if (g_data.env_table)
		free_table(g_data.env_table);
	g_data.env_table = get_env_table();
}
