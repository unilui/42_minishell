/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 00:17:05 by lufelip2          #+#    #+#             */
/*   Updated: 2022/11/11 10:36:23 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	lst_count(t_env *cmd)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = cmd;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	*get_env(char *env)
{
	t_env	*tmp;

	if (!env)
		return (NULL);
	tmp = g_data.extern_env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, env))
			return (tmp->value);
		tmp = tmp->next;
	}
	tmp = g_data.local_env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, env))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

char	**get_env_table(void)
{
	char	**env_table;
	t_env	*env_tmp;
	char	*tmp;
	int		i;

	i = 0;
	env_tmp = g_data.extern_env;
	env_table = malloc((lst_count(g_data.extern_env) + 1) * sizeof(char *));
	if (!env_table)
		return (NULL);
	while (env_tmp)
	{
		tmp = ft_strjoin(env_tmp->key, "=");
		env_table[i] = ft_strjoin(tmp, env_tmp->value);
		free(tmp);
		env_tmp = env_tmp->next;
		i++;
	}
	env_table[i] = NULL;
	return (env_table);
}

char	*get_path(char *executable)
{
	int		i;
	char	*path;

	i = 0;
	while (g_data.path[i])
	{
		path = ft_strjoin(g_data.path[i], executable);
		if (!access(path, X_OK))
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}
