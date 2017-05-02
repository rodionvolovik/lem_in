/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_roots.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvolovik <rvolovik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 20:50:24 by rvolovik          #+#    #+#             */
/*   Updated: 2017/05/02 21:09:06 by rvolovik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void	dfs(t_house *house, int id, t_stk *stk, char *visited)
{
	int		i;

	i = 0;
	if (visited[id] != '1')
	{
		stk = push(stk, id);
		visited[id] = '1';
	}
	while (i < (*house).n)
	{
		if (((*house).matrix)[id][i] == 1 && visited[i] != '1')
			dfs(house, i, stk, visited);
		if (id == (*house).end && stk->id == id)
		{
			(*house).roots = add_root((*house).roots, stk);
			break ;
		}
		i++;
	}
	if (visited[id] == '1')
	{
		stk = pop(stk);
		visited[id] = '0';
	}
}

t_root	*list_switch(t_root *p1, t_root *p2, int *changed)
{
	*changed = 1;
	p1->next = p2->next;
	p2->next = p1;
	return (p2);
}

t_root	*init_sort(int *changed, t_root **p, t_root *head)
{
	t_root	*new;

	*p = NULL;
	*changed = 1;
	new = NULL;
	new = (t_root*)malloc(sizeof(t_root));
	new->next = head;
	return (new);
}

t_root	*sort(t_root *head)
{
	t_root	*p;
	t_root	*q;
	t_root	*top;
	int		changed;

	top = init_sort(&changed, &p, head);
	if (head != NULL && head->next)
	{
		while (changed && !(changed = 0))
		{
			q = top;
			p = top->next;
			while (p->next)
			{
				if (p->len > p->next->len)
					q->next = list_switch(p, p->next, &changed);
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

void	find_roots(t_house *house)
{
	t_stk	*stk;
	char	visited[(*house).n];

	stk = NULL;
	ft_memset(visited, 0, (*house).n);
	dfs(house, (*house).start, stk, visited);
	rootslen((*house).roots);
	sort((*house).roots);
	ft_memset(visited, 0, (*house).n);
	(*house).set = combine_datasets(*house, (*house).set, visited);
}
