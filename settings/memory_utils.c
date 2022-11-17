/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 00:29:46 by lufelip2          #+#    #+#             */
/*   Updated: 2022/11/08 02:02:13 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_table(char **table)
{
	char	**tmp;

	tmp = table;
	while (*table)
		free(*table++);
	free(tmp);
}

void	clear_exec_lst(t_cmd **cmd)
{
	t_cmd	*previous;
	t_cmd	*tmp;

	previous = NULL;
	while (*cmd)
	{
		tmp = *cmd;
		while (tmp->next)
		{
			previous = tmp;
			tmp = tmp->next;
		}
		free_table(tmp->args);
		free(tmp->name);
		if (previous)
			previous->next = NULL;
		if (tmp == *cmd)
			*cmd = NULL;
		free(tmp);
	}
}

void	clear_env_lst(t_env **env)
{
	t_env	*previous;
	t_env	*tmp;

	previous = NULL;
	while (*env)
	{
		tmp = *env;
		while (tmp->next)
		{
			previous = tmp;
			tmp = tmp->next;
		}
		if (tmp->key)
			free(tmp->key);
		if (tmp->value)
			free(tmp->value);
		if (previous)
			previous->next = NULL;
		if (tmp == *env)
			*env = NULL;
		free(tmp);
	}
}
