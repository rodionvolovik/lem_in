/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvolovik <rvolovik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 16:51:49 by rvolovik          #+#    #+#             */
/*   Updated: 2017/04/20 15:24:49 by rvolovik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	ll;

	ll = ft_strlen(little);
	i = 0;
	if (!*little)
		return ((char *)big);
	while (*big && ll <= len - i)
	{
		if (*big == *little && (ft_strncmp(big, little, ll) == 0))
			return ((char *)big);
		big++;
		i++;
	}
	return (NULL);
}
