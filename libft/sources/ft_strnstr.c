/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 10:28:24 by sam               #+#    #+#             */
/*   Updated: 2022/08/25 19:21:56 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_strnstr:
** - Locates the first occurrence of the
**   null-terminated string needle in the string haystack, where not more
**   than len characters are searched.
** - Characters that appear after a `\0' character are not searched.
*/

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	x;
	size_t	y;
	size_t	z;

	x = -1;
	y = 0;
	if (*needle == '\0' || needle == NULL || haystack == needle)
		return ((char *)haystack);
	if (len == 0)
		return (NULL);
	while (++x <= len && haystack[x])
	{
		y = x;
		z = 0;
		if (haystack[x] == needle[0])
		{
			while (haystack[y++] == needle[z++] && y <= len)
			{
				if (needle[z] == '\0')
					return ((char *)haystack + x);
			}
			x++;
		}
	}
	return (NULL);
}
