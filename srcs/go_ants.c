/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_ants.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvolovik <rvolovik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 18:42:33 by rvolovik          #+#    #+#             */
/*   Updated: 2017/05/02 21:56:51 by rvolovik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		setscount(t_set *set)
{
	t_set	*ptr;
	int		n;

	n = 0;
	ptr = set;
	while (ptr)
	{
		n++;
		ptr = ptr->next;
	}
	return (n);
}

void	makemove(t_set *set, int *i, t_house *house, int j)
{
	t_root	*ptr;

	ptr = set->root;
	while (j--)
	{
		if (ptr->stk->next->locked == 0)
		{
			ptr->stk->next->locked = ++(*i);
			ft_putstr("\x1b[1;34mL");
			ft_putnbr(ptr->stk->next->locked);
			ft_putstr("-");
			ft_putstr(roomname(ptr->stk->next->id, *house));
			ft_putstr(" \x1b[0m");
		}
		ptr = ptr->next;
		(*house).start--;
	}
}

void	recway(t_stk **stk, t_house *house)
{
	if ((*stk)->next)
		recway(&(*stk)->next, house);
	if (!(*stk)->next && (*stk)->locked)
	{
		(*stk)->locked = 0;
		(*house).end++;
	}
	else if ((*stk)->next && (*stk)->locked)
	{
		(*stk)->next->locked = (*stk)->locked;
		ft_putstr("\x1b[1;34mL");
		ft_putnbr((*stk)->next->locked);
		ft_putstr("-");
		ft_putstr(roomname((*stk)->next->id, *house));
		ft_putstr(" \x1b[0m");
		(*stk)->locked = 0;
	}
}

void	moveall(t_set *set, t_house *house)
{
	t_set	*ptr;
	t_root	*root;

	ptr = set;
	while (ptr)
	{
		root = ptr->root;
		while (root)
		{
			recway(&root->stk, house);
			root = root->next;
		}
		ptr = ptr->next;
	}
}

void	go_ants(t_house house)
{
	int		i;
	t_set	*set;
	int		j;

	i = 0;
	house.start = house.ants;
	house.end = 0;
	while (house.end < house.ants)
	{
		if (house.end < house.ants)
			moveall(house.set, &house);
		j = 0;
		set = house.set;
		if ((house.start >= set->moves - 1) && set->ways > 1 && house.start > 0)
			makemove(set, &i, &house, set->ways);
		else if (house.start > 0)
		{
			while (set->next)
				set = set->next;
			makemove(set, &i, &house, 1);
		}
		printf("\n");
	}
}
