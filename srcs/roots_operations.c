/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   roots_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvolovik <rvolovik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 21:22:19 by rvolovik          #+#    #+#             */
/*   Updated: 2017/05/02 21:28:27 by rvolovik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_root	*append_root(t_root *head, t_stk *stk)
{
	t_root	*new;
	t_root	*ptr;

	ptr = head;
	new = (t_root*)malloc(sizeof(t_root));
	new->stk = stk;
	new->next = NULL;
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

t_set	*append_set(t_set *set, t_root *root, int id)
{
	t_set	*new;
	t_set	*ptr;

	new = (t_set*)malloc(sizeof(t_set));
	new->root = root;
	new->next = NULL;
	new->id = id;
	ptr = set;
	if (!set)
		set = new;
	else
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
	return (set);
}

int		count_roots(t_root *head)
{
	int		size;
	t_root	*ptr;

	size = 0;
	ptr = head;
	while (ptr)
	{
		size++;
		ptr = ptr->next;
	}
	return (size);
}

void	unvisit(t_stk *stk, int before, char **visited)
{
	t_stk	*ptr;

	ptr = stk;
	while (ptr->next->id != before && ptr->next)
	{
		(*visited)[ptr->id] = 0;
		ptr = ptr->next;
	}
}

t_root	*combine_roots(t_house house, t_root *rts, char *visited)
{
	t_root	*tmp;
	t_root	*new;
	t_stk	*stk;

	new = NULL;
	tmp = rts;
	while (tmp)
	{
		stk = tmp->stk;
		while (stk)
		{
			if (!visited[stk->id])
				visited[stk->id] = 1;
			else if (stk->id != house.start && stk->id != house.end)
				break ;
			stk = stk->next;
		}
		if (stk == NULL)
			new = append_root(new, tmp->stk);
		tmp = tmp->next;
	}
	return (new);
}
