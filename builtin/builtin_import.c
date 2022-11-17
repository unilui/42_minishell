/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_import.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 06:13:18 by lufelip2          #+#    #+#             */
/*   Updated: 2022/11/08 08:18:00 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static void	set_new_var(char *var)
{
	char	**new_var;

	if (!ft_strchr(var, '=') || !(var - ft_strchr(var, '=')))
	{
		g_data.last_exit_code = 1;
		return ;
	}
	new_var = token_split(var, is_value);
	set_extern_env(new_var[0], new_var[1], FALSE);
	set_local_env(new_var[0], new_var[1]);
	free_table(new_var);
	g_data.last_exit_code = 0;
}

void	builtin_import(char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		set_new_var(args[i]);
		i++;
	}
}
