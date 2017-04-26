/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvolovik <rvolovik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 14:58:05 by rvolovik          #+#    #+#             */
/*   Updated: 2017/04/26 20:37:17 by rvolovik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

int   comm(char *line)
{
  if (line[0] == '#' && line[1] != '#')
    return (COMMENT);
  else if (line[0] == '#' && line[1] == '#')
    return (COMMAND);
  return (0);
}

int   number(char *line)
{
  char  *ptr;

  ptr = line;
  while (*ptr)
  {
    if (!ft_isdigit(*ptr))
      return (0);
    ptr++;
  }
  return (1);
}

long long	ft_atoi_long(const char *str)
{
	long long		sign;
	long long		num;

	sign = 1;
	num = 0;
	while ((*str >= 9 && *str <= 13) || (*str == ' '))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10;
		num = num + (*str - '0');
		str++;
	}
	return (sign * num);
}

int   room(char *line)
{
  int   spaces;
  char  *ptr;
  int   n;

  ptr = line;
  n = 0;
  spaces = 0;
  if (line[0] == 'L')
    return (0);
  while (*ptr == ' ')
    ptr++;
  while (*ptr)
  {
    if (*ptr == ' ' && *(ptr + 1) && *(ptr + 1) != ' ' && *(ptr - 1) && *(ptr - 1) != ' ')
    {
      spaces++;
      if (ft_atoi_long(ptr) <= MAX_INT && ft_atoi_long(ptr) >= MIN_INT)
        n++;
    }
    ptr++;
  }
  return (spaces == 2 && n == 2 ? 1 : 0);
}

char  *getname(char *line)
{
  char  *ptr;
  int   len;

  ptr = line;
  while (*ptr)
  {
    if (*ptr == ' ' && *(ptr - 1) &&  *(ptr - 1) != ' ' && *(ptr + 1) && *(ptr + 1) != ' ')
      break ;
    ptr++;
  }
  len = ptr - line;
  return (ft_strsub(line, 0, len));
}

t_room  *append_room(t_room *head, int id, char *line)
{
  t_room  *new;
  t_room  *ptr;

  ptr = head;
  new = (t_room*)malloc(sizeof(t_room));
  new->id = id;
  new->name = getname(line);
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

int   islink(char *line, t_house house, int d)
{
  t_room  *ptr;
  int     len;

  ptr = house.rooms;
  while (ptr)
  {
    len = (d == 1) ? ft_strlen(ptr->name) : ft_strlen(line);
    if (ft_strnequ(line, ptr->name, len))
      break ;
    ptr = ptr->next;
  }
  if (d == 1 && ptr && islink(line + 1 + ft_strlen(ptr->name), house, d - 1))
    return (1);
  if (d == 0 && ptr)
    return (1);
  return (0);
}

void  init_matrix(int ***matrix, t_room *rooms, t_house *house)
{
  t_room  *ptr;
  int     p;
  int     i;
  int     j;

  p = 0;
  i = 0;
  ptr = rooms;
  while (ptr)
  {
    p++;
    ptr = ptr->next;
  }
  (*house).n = p;
  *matrix = (int**)malloc(sizeof(int*) * p);
  while (i < p)
  {
    (*matrix)[i] = (int*)malloc(sizeof(int) * p);
    j = 0;
    while (j < p)
      (*matrix)[i][j++] = 0;
    i++;
  }
}

void add_link(t_house *house, char *line)
{
  int     id1;
  int     id2;
  t_room  *ptr;
  int     len;

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
  id2 = ptr->id;
  if (!(*house).matrix)
    init_matrix(&((*house).matrix), (*house).rooms, house);
  (*house).matrix[id1][id2] = 1;
  (*house).matrix[id2][id1] = 1;
}

int   read_rooms(t_house *house, int fd)
{
  char  *line;
  int   id;

  id = 0;
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

int   read_links(t_house *house, int fd)
{
  char  *line;

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

int   count_ants(int fd)
{
  char  *line;
  int   n;

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

int read_map(t_house *house)
{
  if (!((*house).ants = count_ants(0)))
    return (0);
  if (!(read_rooms(house, 0)))
    return (0);
  if (!(read_links(house, 0)))
    return (0);
  if ((*house).start < 0 || (*house).end < 0)
    return (0);
  return (1);
}
