/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 20:44:31 by lufelip2          #+#    #+#             */
/*   Updated: 2022/11/11 09:29:56 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static int is_single_value(char *str, char *value, int value_len)
{
	int	position;
	int	i;

	position = ft_strnstr(str, value, value_len) - str;
	i = position - 1;
	while (i >= 0)
	{
		if (str[i] != '\'' && str[i] != '\"')
			return (0);
		i--;
	}
	i = position + value_len;
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '\"')
			return (0);
		i++;
	}
	return (1);
}

static int	already_expanded(char *arg)
{
	t_env	*tmp;
	int		arg_len;

	arg_len = ft_strlen(arg);
	tmp = g_data.extern_env;
	while (tmp)
	{
		if (ft_strnstr(arg, tmp->value, arg_len))
			return (is_single_value(arg, tmp->value, arg_len));
		tmp = tmp->next;
	}
	tmp = g_data.local_env;
	while (tmp)
	{
		if (ft_strnstr(arg, tmp->value, arg_len))
			return (is_single_value(arg, tmp->value, arg_len));
		tmp = tmp->next;
	}
	return (0);
}

void	trim_args(void)
{
	t_cmd	*cmd;
	int		i;

	cmd = g_data.cmd;
	if (!cmd)
		return ;
	while (cmd)
	{
		i = 1;
		while (cmd->args[i])
		{
			if (!already_expanded(cmd->args[i]))
				trim_quotes(&cmd->args[i]);
			i++;
		}
		cmd = cmd->next;
	}
}
