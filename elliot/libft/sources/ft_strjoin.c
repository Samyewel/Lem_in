/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 15:13:09 by swilliam          #+#    #+#             */
/*   Updated: 2022/08/25 19:21:23 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_strjoin:
** - Allocates (with malloc(3)) and returns a “fresh” string ending
**   with ’\0’, being the result of the concatenation of s1 and s2.
** - If the allocation fails the function returns NULL.
*/

static char	*join_strings(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*join;
	size_t	x;
	size_t	y;

	x = -1;
	y = -1;
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	join = ft_strnew(s1_len + s2_len);
	if (!(join))
		return (NULL);
	while (++x < s1_len + s2_len)
	{
		if (x < s1_len)
			join[x] = s1[x];
		if (x >= s1_len && ++y <= s2_len)
			join[x] = s2[y];
	}
	join[x] = '\0';
	return (join);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;

	if (s1 && s2)
	{
		join = join_strings(s1, s2);
		return (join);
	}
	return (NULL);
}
