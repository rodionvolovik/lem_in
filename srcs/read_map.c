/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvolovik <rvolovik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 14:58:05 by rvolovik          #+#    #+#             */
/*   Updated: 2017/05/02 20:52:41 by rvolovik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void	add_link(t_house *house, char *line)
{
	int		id1;
	t_room	*ptr;
	int		len;

	ptr = (*house).rooms;
	while (ptr)
	{
		if (ft_strnequ(line, ptr->name, ft_strlen(ptr->name)))
			break ;
		ptr = ptr->next;
	}
	id1 = ptr->id;
	len = ft_strlen(ptr->name);
	ptr = (*house).rooms;
	while (ptr)
	{
		if (ft_strnequ(ptr->name, line + 1 + len, ft_strlen(line + 1 + len)))
			break ;
		ptr = ptr->next;
	}
	if (!(*house).matrix)
		init_matrix(&((*house).matrix), (*house).rooms, house);
	(*house).matrix[id1][ptr->id] = 1;
	(*house).matrix[ptr->id][id1] = 1;
}

int		read_rooms(t_house *house, int fd, int id)
{
	char	*line;

	line = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		if (comm(line))
		{
			if (ft_strequ(line, START))
				(*house).start = id;
			else if (ft_strequ(line, END))
				(*house).end = id;
		}
		else if (room(line))
			(*house).rooms = append_room((*house).rooms, id++, line);
		else
			break ;
		free(line);
	}
	if (islink(line, *house, 1))
		add_link(house, line);
	else
		return (0);
	free(line);
	return (1);
}

int		read_links(t_house *house, int fd)
{
	char	*line;

	line = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		if (comm(line) && !ft_strequ(line, START) && !ft_strequ(line, END))
		{
			free(line);
			continue ;
		}
		if (islink(line, *house, 1))
			add_link(house, line);
		else
			return (0);
		free(line);
	}
	free(line);
	return (1);
}

int		count_ants(int fd)
{
	char	*line;
	int		n;

	line = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		if (comm(line) && !(ft_strequ(line, START) || ft_strequ(line, END)))
			free(line);
		else
			break ;
	}
	n = ft_atoi(line);
	free(line);
	return (n);
}

int		read_map(t_house *house)
{
	if (!((*house).ants = count_ants(0)))
		return (0);
	if (!(read_rooms(house, 0, 0)))
		return (0);
	if (!(read_links(house, 0)))
		return (0);
	if ((*house).start < 0 || (*house).end < 0)
		return (0);
	return (1);
}
