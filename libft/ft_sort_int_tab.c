/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_int_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 17:08:29 by lufelip2          #+#    #+#             */
/*   Updated: 2022/10/16 19:40:32 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*

Sorts an array of integers by ascending order.

*/

void	ft_sort_int_tab(int *tab, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (i == size - 1)
		{
			if (tab[i] < tab[i - i])
			{
				ft_swap(&tab[i], &tab[i - i]);
				i = 0;
				continue ;
			}
		}
		else
		{
			if (tab[i] > tab[i + 1])
			{
				ft_swap(&tab[i], &tab[i + 1]);
				i = 0;
				continue ;
			}
		}
		i++;
	}
}
