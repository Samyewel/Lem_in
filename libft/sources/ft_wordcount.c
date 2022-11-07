/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordcount.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:33:20 by sam               #+#    #+#             */
/*   Updated: 2022/08/25 19:22:20 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_wordcount:
** - Counts how many individual words there are in a single string.
*/

size_t	ft_wordcount(char const *s, char c)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (!s)
		return (0);
	while (s[x])
	{
		while (s[x] == c)
			x++;
		if (s[x] != c && s[x])
			y++;
		while (s[x] != c && s[x])
			x++;
	}
	return (y);
}
