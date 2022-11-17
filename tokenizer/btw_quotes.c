/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btw_quotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 02:39:41 by lufelip2          #+#    #+#             */
/*   Updated: 2022/11/08 11:06:33 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	btw_quotes(int position, char const *line)
{
	int	double_quotes;
	int	single_quotes;

	double_quotes = 0;
	single_quotes = 0;
	while (position >= 0)
	{
		if (line[position] == '\"')
			double_quotes++;
		if (line[position] == '\'')
			single_quotes++;
		position--;
	}
	return ((double_quotes % 2) || (single_quotes % 2));
}
