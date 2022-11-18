/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 03:38:19 by lufelip2          #+#    #+#             */
/*   Updated: 2022/11/17 19:26:14 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static int	is_valid_name(char *var)
{
	int	i;
	int	letter;

	i = 0;
	letter = 0;
	if (!ft_strcmp(var, "="))
		return (0);
	while (var[i])
	{
		if (!ft_isalnum(var[i]) && var[i] != '='
			&& ft_strchr(var, '=') > ft_strchr(var, var[i]))
			return (0);
		if (ft_isalpha(var[i])
			&& (ft_strchr(var, var[i]) < ft_strchr(var, '=')
				|| !ft_strchr(var, '=')))
			letter = 1;
		i++;
	}
	if (!letter)
		return (0);
	return (1);
}

static void	set_new_var(char *var)
{
	char	**new_var;

	if (!is_valid_name(var))
	{
		ft_printf("export: not a valid identifier: '%s'\n", var);
		return ;
	}
	if (!ft_strchr(var, '='))
	{
		g_data.last_exit_code = 1;
		return ;
	}
	new_var = token_split(var, is_value);
	set_extern_env(new_var[0], new_var[1], TRUE);
	free_table(new_var);
	g_data.last_exit_code = 0;
}

void	builtin_export(char **args)
{
	int	args_nbr;
	int	i;

	i = 1;
	args_nbr = table_size(args);
	if (args_nbr == 1)
	{
		builtin_env(g_data.extern_env, TRUE);
		return ;
	}
	while (i < args_nbr)
	{
		set_new_var(args[i]);
		i++;
	}
}
