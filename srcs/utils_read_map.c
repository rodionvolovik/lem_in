/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_read_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvolovik <rvolovik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 19:58:12 by rvolovik          #+#    #+#             */
/*   Updated: 2017/05/02 21:02:16 by rvolovik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			comm(char *line)
{
	if (line[0] == '#' && line[1] != '#')
		return (COMMENT);
	else if (line[0] == '#' && line[1] == '#')
		return (COMMAND);
	return (0);
}

int			number(char *line)
{
	char	*ptr;

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
	long long	sign;
	long long	num;

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

int			room(char *line)
{
	int		spaces;
	char	*ptr;
	int		n;

	ptr = line;
	n = 0;
	spaces = 0;
	if (line[0] == 'L')
		return (0);
	while (*ptr == ' ')
		ptr++;
	while (*ptr)
	{
		if (*ptr == ' ' && *(ptr + 1) && *(ptr + 1) != ' '
				&& *(ptr - 1) && *(ptr - 1) != ' ')
		{
			spaces++;
			if (ft_atoi_long(ptr) <= MAX_INT && ft_atoi_long(ptr) >= MIN_INT)
				n++;
		}
		ptr++;
	}
	return (spaces == 2 && n == 2 ? 1 : 0);
}

char		*getname(char *line)
{
	char	*ptr;
	int		len;

	ptr = line;
	while (*ptr)
	{
		if (*ptr == ' ' && *(ptr - 1) &&
				*(ptr - 1) != ' ' && *(ptr + 1) && *(ptr + 1) != ' ')
			break ;
		ptr++;
	}
	len = ptr - line;
	return (ft_strsub(line, 0, len));
}
