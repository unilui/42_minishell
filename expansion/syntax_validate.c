/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_validate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 19:31:23 by lufelip2          #+#    #+#             */
/*   Updated: 2022/11/18 20:44:01 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	syntax_validate(void)
{
	if (!g_data.line)
		return ;
	if (wrong_op()
		|| unexpected_token()
		|| open_quotes()
		|| sequence_op())
	{
		free(g_data.line);
		g_data.line = NULL;
	}
}
