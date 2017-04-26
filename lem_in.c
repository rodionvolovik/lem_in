/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvolovik <rvolovik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 13:58:43 by rvolovik          #+#    #+#             */
/*   Updated: 2017/04/26 21:00:19 by rvolovik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void print_hui(t_house house)
{
  printf("Number of ants = %d\n", house.ants);

  t_room  *roomptr;
  roomptr = house.rooms;
  while (roomptr)
  {
    printf("name '%s' id {%d}\n", roomptr->name, roomptr->id);
    roomptr = roomptr->next;
  }

  printf("number of rooms %d\n", house.n);
  int   i = 0, j;
  int   **m = house.matrix;
  while (i < house.n)
  {
    j = 0;
    while (j < house.n)
    {
      printf("%2d", m[i][j]);
      j++;
    }
    printf("\n");
    i++;
  }
}

void ft_error(char *error_mesage)
{
  ft_putendl(error_mesage);
  exit(0);
}

void init_house(t_house *house)
{
  (*house).ants = 0;
  (*house).n = 0;
  (*house).start = -1;
  (*house).end = -1;
  (*house).matrix = NULL;
  (*house).rooms = NULL;
}

int   main(void)
{
  t_house house;
  t_root  *roots;

  roots = NULL;
  init_house(&house);
  if (!read_map(&house))
    ft_error(ERROR);
  find_roots(roots, house);

  print_hui(house);
  // while (1) ;
  return (0);
}
