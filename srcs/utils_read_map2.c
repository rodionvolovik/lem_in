/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_read_map2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvolovik <rvolovik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 20:20:25 by rvolovik          #+#    #+#             */
/*   Updated: 2017/05/02 21:03:51 by rvolovik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		numsize(char *line)
{
	int		size;
	char	*ptr;

	size = 0;
	ptr = line;
	while (*ptr)
	{
		size++;
		if (*ptr != ' ' && *(ptr - 1) == ' ')
			break ;
		ptr++;
	}
	return (size);
}

void	comparecoords(t_room *head, t_room *new)
{
	t_room	*ptr;

	ptr = head;
	if (head)
	{
		while (ptr)
		{
			if (ptr->x == new->x && ptr->y == new->y)
				ft_error(ERROR);
			ptr = ptr->next;
		}
	}
}

t_room	*append_room(t_room *head, int id, char *line)
{
	t_room	*new;
	t_room	*ptr;
	t_room	*tmp;

	ptr = head;
	tmp = head;
	new = (t_room*)malloc(sizeof(t_room));
	new->id = id;
	new->name = getname(line);
	new->x = atoi(line + ft_strlen(new->name));
	new->y = atoi(line + ft_strlen(new->name) + numsize(line));
	new->next = NULL;
	comparecoords(head, new);
	if (!head)
		head = new;
	else
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
	return (head);
}

int		islink(char *line, t_house house, int d)
{
	t_room	*ptr;
	int		len;

	ptr = house.rooms;
	while (ptr)
	{
		len = (d == 1) ? ft_strlen(ptr->name) : ft_strlen(line);
		if (ft_strnequ(line, ptr->name, len))
			break ;
		ptr = ptr->next;
	}
	if (d == 1 && ptr && islink(line + 1 + ft_strlen(ptr->name), house, d - 1))
		return (1);
	if (d == 0 && ptr)
		return (1);
	return (0);
}

void	init_matrix(int ***matrix, t_room *rooms, t_house *house)
{
	t_room	*ptr;
	int		p;
	int		i;
	int		j;

	p = 0;
	i = 0;
	ptr = rooms;
	while (ptr)
	{
		p++;
		ptr = ptr->next;
	}
	(*house).n = p;
	*matrix = (int**)malloc(sizeof(int*) * p);
	while (i < p)
	{
		(*matrix)[i] = (int*)malloc(sizeof(int) * p);
		j = 0;
		while (j < p)
			(*matrix)[i][j++] = 0;
		i++;
	}
}
