/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 10:52:17 by sam               #+#    #+#             */
/*   Updated: 2022/08/25 19:20:59 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_strchr:
** - Locates the first occurrence of c (converted to a char) in the
**   string pointed to by s.
** - The terminating null character is considered to be part of the
**   string; therefore if c is `\0', the functions locate the terminating `\0'.
*/

char	*ft_strchr(const char *s, int c)
{
	int	x;

	x = 0;
	while (s[x])
	{
		if (s[x] == c)
			return ((char *)s + x);
		x++;
	}
	if (s[x] == '\0' && s[x] == c)
		return ((char *)s + x);
	return (NULL);
}
