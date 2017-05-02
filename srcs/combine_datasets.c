/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combine_datasets.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvolovik <rvolovik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 13:03:43 by rvolovik          #+#    #+#             */
/*   Updated: 2017/05/02 21:36:17 by rvolovik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	count_params(t_set *set)
{
	int		ways;
	int		moves;
	t_set	*st;
	t_root	*rt;

	st = set;
	while (st)
	{
		ways = 0;
		moves = 0;
		rt = st->root;
		while (rt)
		{
			ways++;
			rootslen(rt);
			moves += rt->len;
			rt = rt->next;
		}
		st->ways = ways;
		st->moves = moves;
		st = st->next;
	}
}

t_set	*set_switch(t_set *p1, t_set *p2, int *changed)
{
	*changed = 1;
	p1->next = p2->next;
	p2->next = p1;
	return (p2);
}

t_set	*init_set_sort(int *changed, t_set **p, t_set *head)
{
	t_set	*new;

	*p = NULL;
	*changed = 1;
	new = (t_set*)malloc(sizeof(t_set));
	new->next = head;
	return (new);
}

t_set	*sortsets(t_set *head)
{
	t_set	*p;
	t_set	*q;
	t_set	*top;
	int		changed;

	top = init_set_sort(&changed, &p, head);
	if (top->next)
	{
		while (changed && !(changed = 0))
		{
			q = top;
			p = top->next;
			while (p->next)
			{
				if (p->moves < p->next->moves)
					q->next = set_switch(p, p->next, &changed);
				q = p;
				if (p->next)
					p = p->next;
			}
		}
		p = top->next;
	}
	free(top);
	return (p);
}

t_set	*combine_datasets(t_house house, t_set *set, char *visited)
{
	t_root	*rts;
	t_root	*new;
	int		id;

	id = 0;
	rts = house.roots;
	while (rts)
	{
		new = NULL;
		new = combine_roots(house, rts, visited);
		if (new)
		{
			set = append_set(set, new, id);
			id++;
		}
		ft_memset(visited, 0, house.n);
		rts = rts->next;
	}
	count_params(set);
	set = sortsets(set);
	return (set);
}
