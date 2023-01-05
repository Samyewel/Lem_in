/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 12:02:53 by sam               #+#    #+#             */
/*   Updated: 2022/08/25 19:21:39 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_strncat:
** - Appends not more than n characters from s2, and then adds a
**   terminating `\0'.
*/

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t	x;
	size_t	y;
	char	*ammend;

	x = 0;
	y = 0;
	ammend = s1;
	if (n < 0)
		return (NULL);
	while (s1[x] != '\0')
		x++;
	if (s1[x] == '\0')
	{
		while (y < n)
		{
			s1[x] = s2[y];
			if (s2[y] == '\0')
				return (ammend);
			y++;
			x++;
		}
	}
	s1[x] = '\0';
	return (ammend);
}
