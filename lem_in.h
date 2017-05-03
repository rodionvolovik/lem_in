/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfdf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvolovik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 22:14:21 by rvolovik          #+#    #+#             */
/*   Updated: 2017/05/03 11:51:04 by rvolovik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "get_next_line.h"
# include <stdlib.h>

# define ERROR "\x1b[31mError\x1b[0m"
# define MAX_INT 2147483647
# define MIN_INT -2147483648
# define START "##start"
# define END "##end"
# define COMMAND 1
# define COMMENT 2

typedef struct		s_stk
{
	int				id;
	int				locked;
	struct s_stk	*next;
}					t_stk;

typedef struct		s_room
{
	int				id;
	char			*name;
	int				x;
	int				y;
	struct s_room	*next;
}					t_room;

typedef struct		s_root
{
	int				len;
	int				used;
	t_stk			*stk;
	struct s_root	*next;
}					t_root;

typedef struct		s_set
{
	int				id;
	int				ways;
	int				moves;
	t_root			*root;
	struct s_set	*next;
}					t_set;

typedef struct		s_house
{
	int				ants;
	int				n;
	int				start;
	int				end;
	int				**matrix;
	t_room			*rooms;
	t_root			*roots;
	t_set			*set;
}					t_house;

/*
**  lem_in.c
*/
char				*roomname(int id, t_house house);
void				ft_error(char *error_mesage);
/*
**  get_next_line/get_next_line.c
*/
int					get_next_line(const int fd, char **line);
/*
**  srcs/read_map.c
*/
int					read_map(t_house *house);
/*
**  srcs/utils_read_map.c
*/
int					comm(char *line);
int					room(char *line);
char				*getname(char *line);
/*
**  srcs/stack_operations.c
*/
t_stk				*pop(t_stk *head);
t_stk				*push(t_stk *head, int id);
t_root				*add_root(t_root *head, t_stk *stk);
/*
**  srcs/utils_read_map2.c
*/
t_room				*append_room(t_room *head, int id, char *line);
void				init_matrix(int ***matrix, t_room *rooms, t_house *house);
int					islink(char *line, t_house house, int d);
/*
**  srcs/find_roots.c
*/
void				rootslen(t_root *head);
void				find_roots(t_house *house);
/*
**  srcs/combine_datasets.c
*/
t_set				*combine_datasets(t_house house, t_set *set, char *visited);
/*
**  srcs/go_ants.c
*/
void				go_ants(t_house house);
/*
**  srcs/roots_operations.c
*/
t_set				*append_set(t_set *set, t_root *root, int id);
t_root				*combine_roots(t_house house, t_root *rts, char *visited);

#endif
