/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 04:23:42 by lufelip2          #+#    #+#             */
/*   Updated: 2022/11/11 21:12:40 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static void	unset_var(t_env **head, char *var)
{
	t_env	*previous;
	t_env	*tmp;

	tmp = *head;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, var))
		{
			if (tmp == *head)
				*head = tmp->next;
			else
				previous->next = tmp->next;
			if (tmp->key)
				free(tmp->key);
			if (tmp->value)
				free(tmp->value);
			free(tmp);
		}
		previous = tmp;
		tmp = tmp->next;
	}
}

void	builtin_unset(char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		unset_var(&g_data.extern_env, args[i]);
		unset_var(&g_data.local_env, args[i]);
		if (!ft_strcmp(args[i], "PATH"))
			set_exec_path();
		i++;
	}
	g_data.last_exit_code = 0;
}
