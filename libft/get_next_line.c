/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 21:26:01 by lufelip2          #+#    #+#             */
/*   Updated: 2022/10/16 19:44:24 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"

static t_file	*find_or_add_fd(t_file **head, int fd);
static t_file	*add_fd(t_file **head, int fd);
static char		*delete_fd(t_file **head, int fd);
static char		*get_line(t_file **head, t_file *file);

/*

Returns a line read from a file descriptor (fd).

*/

char	*get_next_line(int fd)
{
	static t_file	*file_table = NULL;
	t_file			*file;

	file = find_or_add_fd(&file_table, fd);
	if (file)
	{
		while (ft_chrpst(file->line, '\n') == -1)
		{
			file->rdd = read(file->fd, file->buffer, BUFFER_SIZE);
			if (file->rdd == 0 && !file->line)
				return (delete_fd(&file_table, file->fd));
			file->buffer[file->rdd] = '\0';
			file->tmp = file->line;
			file->line = ft_strjoin(file->tmp, file->buffer);
			free(file->tmp);
			if (file->rdd < BUFFER_SIZE)
				return (get_line(&file_table, file));
		}
		return (get_line(&file_table, file));
	}
	return (NULL);
}

static char	*get_line(t_file **head, t_file *file)
{
	char	*next_line;
	int		new_line;
	int		line;
	int		end;

	free(file->buffer);
	line = ft_strlen(file->line);
	new_line = ft_chrpst(file->line, '\n') + 1;
	if (new_line == 0)
		new_line = line;
	end = line - new_line;
	file->buffer = ft_substr(file->line, 0, new_line);
	file->tmp = file->line;
	file->line = ft_substr(file->tmp, new_line, end);
	free(file->tmp);
	next_line = ft_strdup(file->buffer);
	free(file->buffer);
	file->tmp = NULL;
	file->buffer = NULL;
	if (!file->line)
		delete_fd(head, file->fd);
	return (next_line);
}

static t_file	*find_or_add_fd(t_file **head, int fd)
{
	t_file	*tmp;

	if (fd < 0)
	{
		delete_fd(head, -(fd));
		return (NULL);
	}
	tmp = *head;
	while (tmp)
	{
		if (tmp->fd == fd)
		{
			tmp->buffer = malloc(BUFFER_SIZE + 1);
			if (!tmp->buffer)
				return (NULL);
			return (tmp);
		}
		tmp = tmp->next;
	}
	return (add_fd(head, fd));
}

static t_file	*add_fd(t_file **head, int fd)
{
	t_file	*tmp;

	tmp = malloc(sizeof(t_file));
	if (!tmp)
		return (NULL);
	tmp->fd = fd;
	tmp->line = NULL;
	tmp->buffer = malloc(BUFFER_SIZE + 1);
	if (!tmp->buffer)
		return (NULL);
	tmp->next = *head;
	*head = tmp;
	return (*head);
}

static char	*delete_fd(t_file **head, int fd)
{
	t_file	*previous;
	t_file	*tmp;

	tmp = *head;
	while (tmp)
	{
		if (tmp->fd == fd)
		{
			if (tmp == *head)
				*head = tmp->next;
			else
				previous->next = tmp->next;
			if (tmp->buffer)
				free(tmp->buffer);
			if (tmp->line)
				free(tmp->line);
			free(tmp);
			return (NULL);
		}
		previous = tmp;
		tmp = tmp->next;
	}
	return (NULL);
}
