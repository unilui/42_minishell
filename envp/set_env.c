/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 22:10:57 by lufelip2          #+#    #+#             */
/*   Updated: 2022/11/08 08:48:52 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	set_extern_env(char *key, char *value, int add)
{
	t_env	*tmp;

	tmp = g_data.extern_env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			if (tmp->value)
				free(tmp->value);
			tmp->value = ft_strdup(value);
			break ;
		}
		tmp = tmp->next;
	}
	if (!tmp && add)
		env_lst_add(&g_data.extern_env, create_var(key, value));
	if (!ft_strcmp(key, "PATH"))
		set_exec_path();
	set_env_table();
}

void	set_local_env(char *key, char *value)
{
	t_env	*tmp;

	tmp = g_data.local_env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			if (tmp->value)
				free(tmp->value);
			tmp->value = ft_strdup(value);
			break ;
		}
		tmp = tmp->next;
	}
	if (!tmp)
		env_lst_add(&g_data.local_env, create_var(key, value));
}
