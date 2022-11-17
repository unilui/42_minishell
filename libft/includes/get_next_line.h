/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 00:08:22 by lufelip2          #+#    #+#             */
/*   Updated: 2022/09/13 00:57:33 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFFER_SIZE 4096

typedef struct s_file {
	int				fd;
	int				rdd;
	char			*line;
	char			*buffer;
	char			*tmp;
	struct s_file	*next;
}	t_file;

#endif
