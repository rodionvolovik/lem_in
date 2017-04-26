/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_roots.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvolovik <rvolovik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 20:50:24 by rvolovik          #+#    #+#             */
/*   Updated: 2017/04/26 21:08:47 by rvolovik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_stk *pop(t_stk *head)
{
  t_stk *tmp;

  if (head)
  {
    tmp = head->next;
    free(head);
  }
  return(tmp);
}

t_stk *push(t_stk *head, int id)
{
  t_stk *new;

  new = (t_stk*)malloc(sizeof(t_stk));
  new->next = NULL;
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

void dfs(t_root **roots, t_house house)
{
  
}

void find_roots(t_root *roots, t_house house)
{
  t_stk *stk;
  char  *visited[house.n];
  int   i;

  ft_memset(visited, 0, house.n);
  dfs(&roots, house);
  stk = NULL;
}
