/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 11:59:20 by sam               #+#    #+#             */
/*   Updated: 2022/08/25 19:20:57 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_strcat:
** - Appends a copy of the null-terminated string s2 to the end of the
**   null-terminated string s1, then add a terminating `\0'.
** - The string s1 must have sufficient space to hold the result.
*/

char	*ft_strcat(char *s1, const char *s2)
{
	int		x;
	int		y;
	char	*ammend;

	x = 0;
	y = 0;
	ammend = s1;
	while (s1[x] != '\0')
		x++;
	if (s1[x] == '\0')
	{
		while (s2[y] != '\0')
		{
			s1[x] = s2[y];
			x++;
			y++;
		}
	}
	s1[x] = '\0';
	return (ammend);
}
