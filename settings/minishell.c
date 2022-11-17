/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 00:29:53 by lufelip2          #+#    #+#             */
/*   Updated: 2022/11/13 20:06:16 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

t_data	g_data;

int	main(int argc, char **argv, char **envp)
{
	shell_init(envp);
	while (TRUE)
	{
		prompt();
		syntax_validate();
		handle_spaces();
		var_expand();
		tokenizer();
		trim_args();
		execution();
	}
	(void)argc;
	(void)argv;
}
