/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvolovik <rvolovik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 13:58:02 by rvolovik          #+#    #+#             */
/*   Updated: 2017/04/26 21:05:54 by rvolovik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "get_next_line.h"
# include <stdlib.h>

# include <stdio.h>//FOR DELETE; CLEAR ALL PRINTF STATEMENTS!

# define ERROR "\x1b[31mError\x1b[0m"
# define MAX_INT 2147483647
# define MIN_INT -2147483648
# define START "##start"
# define END "##end"
# define COMMAND 1
# define COMMENT 2

typedef struct  s_stk
{
  int           id;
  struct s_stk  *next;
}               t_stk;

typedef struct  s_room
{
  int           id;//id of room in graph
  char          *name;//room name from map
  struct s_room *next;//link to the next room
}               t_room;

typedef struct  s_root
{
  t_stk         *stk;
  struct s_root *next;
}               t_root;

typedef struct  s_house
{
  int           ants;//number of ants
  int           n;//number of rooms
  int           start;
  int           end;
  int           **matrix;//graph
  t_room        *rooms;//rooms in graph
}               t_house;

/*
**  get_next_line/get_next_line.c
*/
int             get_next_line(const int fd, char **line);
/*
**  srcs/read_map.c
*/
int             read_map(t_house *house);

#endif
