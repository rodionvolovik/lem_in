/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvolovik <rvolovik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 14:36:51 by rvolovik          #+#    #+#             */
/*   Updated: 2017/04/19 18:32:25 by rvolovik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_gnl	*pick_file(t_gnl **list, const int fd)
{
	t_gnl	*tmp;
	t_gnl	*new;

	if (*list == NULL)
	{
		(*list) = (t_gnl*)malloc(sizeof(t_gnl));
		(*list)->fd = fd;
		(*list)->saved = NULL;
		(*list)->next = NULL;
	}
	tmp = *list;
	while (tmp != NULL)
	{
		new = tmp;
		if (tmp->fd == fd)
			return (tmp);
		tmp = tmp->next;
	}
	new->next = (t_gnl*)malloc(sizeof(t_gnl));
	new->next->fd = fd;
	new->next->saved = NULL;
	new->next->next = NULL;
	return (new->next);
}

int		get_line(char **saved, char *buf, char **line)
{
	char	*break_point;
	char	*tmp;

	if (!*saved)
		*saved = ft_strdup(buf);
	else
	{
		tmp = ft_strjoin(*saved, buf);
		ft_memset(buf, '\0', BUFF_SIZE + 1);
		free(*saved);
		*saved = tmp;
		if ((break_point = ft_strchr(*saved, '\n')))
		{
			*break_point = '\0';
			tmp = ft_strdup(break_point + 1);
			*line = ft_strdup(*saved);
			ft_strdel(saved);
			*saved = tmp;
			return (1);
		}
	}
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	static t_gnl	*list;
	t_gnl			*current;
	char			*buf;
	int				read_num;

	if (!(buf = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1))) || fd < 0
		|| read(fd, buf, 0) || !line)
		return (-1);
	ft_memset(buf, '\0', BUFF_SIZE + 1);
	current = pick_file(&list, fd);
	if ((get_line(&(current->saved), buf, line)))
	{
		free(buf);
		return (1);
	}
	while ((read_num = read(fd, buf, BUFF_SIZE)))
		if ((get_line(&(current->saved), buf, line)))
		{
			free(buf);
			return (1);
		}
	if (*current->saved)
	{
		*line = ft_strdup(current->saved);
		ft_strdel(&(current->saved));
		free(buf);
		return (1);
	}
	return (read_num == -1 ? -1 : 0);
}
