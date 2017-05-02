/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvolovik <rvolovik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 20:55:24 by rvolovik          #+#    #+#             */
/*   Updated: 2017/05/02 20:59:34 by rvolovik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_stk	*pop(t_stk *head)
{
	t_stk	*tmp;

	tmp = NULL;
	if (head)
	{
		tmp = head->next;
		free(head);
	}
	return (tmp);
}

t_stk	*push(t_stk *head, int id)
{
	t_stk	*new;

	new = (t_stk*)malloc(sizeof(t_stk));
	new->next = NULL;
	new->locked = 0;
	new->id = id;
	if (!head)
		head = new;
	else
	{
		new->next = head;
		head = new;
	}
	return (head);
}

int		stk_size(t_stk *head)
{
	t_stk	*ptr;
	int		size;

	size = 0;
	ptr = head;
	while (ptr)
	{
		size++;
		ptr = ptr->next;
	}
	return (size);
}

t_root	*add_root(t_root *head, t_stk *stk)
{
	t_stk	*ptr;
	t_root	*new;

	new = (t_root*)malloc(sizeof(t_root));
	new->len = 0;
	new->stk = NULL;
	new->next = NULL;
	ptr = stk;
	while (ptr)
	{
		new->stk = push(new->stk, ptr->id);
		ptr = ptr->next;
	}
	if (!head)
		head = new;
	else
	{
		new->next = head;
		head = new;
	}
	return (head);
}

void	rootslen(t_root *head)
{
	t_root	*ptr;
	int		len;
	t_stk	*stk;

	ptr = head;
	if (!head)
		ft_error(ERROR);
	while (ptr)
	{
		stk = ptr->stk;
		len = 0;
		while (stk)
		{
			len++;
			stk = stk->next;
		}
		ptr->len = len - 1;
		ptr = ptr->next;
	}
}
