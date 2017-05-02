/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvolovik <rvolovik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 13:58:43 by rvolovik          #+#    #+#             */
/*   Updated: 2017/05/02 22:07:01 by rvolovik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char	*roomname(int id, t_house house)
{
	t_room	*ptr;

	ptr = house.rooms;
	while (ptr)
	{
		if (id == ptr->id)
			return (ptr->name);
		ptr = ptr->next;
	}
	return (NULL);
}

void	ft_error(char *error_mesage)
{
	ft_putendl(error_mesage);
	exit(0);
}

void	init_house(t_house *house)
{
	(*house).ants = 0;
	(*house).n = 0;
	(*house).start = -1;
	(*house).end = -1;
	(*house).matrix = NULL;
	(*house).rooms = NULL;
	(*house).roots = NULL;
	(*house).set = NULL;
}

int		main(void)
{
	t_house	house;
	t_root	*roots;

	roots = NULL;
	init_house(&house);
	if (!read_map(&house))
		ft_error(ERROR);
	find_roots(&house);
	go_ants(house);
	return (0);
}
