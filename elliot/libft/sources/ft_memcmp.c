/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 16:17:09 by swilliam          #+#    #+#             */
/*   Updated: 2022/08/25 19:20:18 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_memcmp:
** - The memcmp() function compares byte string s1 against byte string s2.
** - Both strings are assumed to be n bytes long.
** - Returns zero if the two strings are identical, otherwise 1, 0, or -1
**   depending on whether the first string is greater than, equal or lesser
**   than the second string.
** - Treated as unsigned char values, so that `\200' is greater than `\0',
**   for example.
**   Zero-length strings are always identical.
*/

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*str1;
	const unsigned char	*str2;
	size_t				x;

	str1 = (const unsigned char *) s1;
	str2 = (const unsigned char *) s2;
	x = 0;
	while (x < n)
	{
		if (str1[x] != str2[x])
			return (str1[x] - str2[x]);
		x++;
	}
	return (0);
}
