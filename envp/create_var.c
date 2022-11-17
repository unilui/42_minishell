/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 00:16:54 by lufelip2          #+#    #+#             */
/*   Updated: 2022/09/28 00:27:10 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

t_env	*create_var(char *key, char *value)
{
	t_env	*result;

	result = malloc(sizeof(t_env));
	if (!result)
		return (0);
	result->key = ft_strdup(key);
	result->value = ft_strdup(value);
	result->next = NULL;
	return (result);
}
