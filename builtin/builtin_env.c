/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 20:26:40 by lufelip2          #+#    #+#             */
/*   Updated: 2022/11/11 16:52:43 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	builtin_env(t_env *env, int export)
{
	while (env)
	{
		if (export)
			ft_printf("declare -x ");
		ft_printf("%s=", env->key);
		if (export)
			ft_printf("\"");
		ft_printf("%s", env->value);
		if (export)
			ft_printf("\"");
		ft_printf("\n");
		env = env->next;
	}
	g_data.last_exit_code = 0;
}
