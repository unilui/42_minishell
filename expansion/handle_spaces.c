/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_spaces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 06:23:10 by lufelip2          #+#    #+#             */
/*   Updated: 2022/11/17 19:37:56 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static void	add_before(int i)
{
	char	*tmp;
	char	*tmp_i;

	tmp = ft_substr(g_data.line, 0, i);
	tmp_i = ft_strjoin(tmp, " ");
	free(tmp);
	tmp = ft_substr(g_data.line, i, ft_strlen(g_data.line));
	free(g_data.line);
	g_data.line = ft_strjoin(tmp_i, tmp);
	free(tmp);
	free(tmp_i);
}

static void	add_after(int i)
{
	char	*tmp;
	char	*tmp_i;

	tmp = ft_substr(g_data.line, 0, i + 1);
	tmp_i = ft_strjoin(tmp, " ");
	free(tmp);
	tmp = ft_substr(g_data.line, i + 1, ft_strlen(g_data.line));
	free(g_data.line);
	g_data.line = ft_strjoin(tmp_i, tmp);
	free(tmp);
	free(tmp_i);
}

static void	add_spaces(void)
{
	int	i;

	i = 0;
	while (g_data.line[i])
	{
		if (i > 0
			&& is_operator(i, g_data.line)
			&& !is_operator(i - 1, g_data.line)
			&& g_data.line[i - 1] != ' ')
			add_before(i);
		if (g_data.line[i + 1]
			&& is_operator(i, g_data.line)
			&& !is_operator(i + 1, g_data.line)
			&& g_data.line[i + 1] != ' ')
			add_after(i);
		i++;
	}
}

//static void	truncate_spaces(void)
//{
//	char	**tokens;
//
//	tokens = ft_split(g_data.line, ' ');
//	free(g_data.line);
//	g_data.line = table_join(tokens, " ");
//	free_table(tokens);
//}

void	handle_spaces(void)
{
	if (!g_data.line)
		return ;
	add_spaces();
}
