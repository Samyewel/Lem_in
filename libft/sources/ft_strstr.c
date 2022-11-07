/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 16:13:12 by swilliam          #+#    #+#             */
/*   Updated: 2022/08/25 19:22:07 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_strstr:
** - Locates the first occurrence of the null-terminated
**   string 'needle' in the null-terminated string 'haystack'.
*/

char	*ft_strstr(const char *haystack, const char *needle)
{
	int		x;
	int		y;
	int		z;

	x = 0;
	y = 0;
	z = 0;
	if (!*needle)
		return ((char *)haystack);
	while (haystack[x])
	{
		y = x;
		z = 0;
		if (haystack[x] == needle[0])
		{
			while (haystack[y++] == needle[z++])
			{
				if (needle[z] == '\0')
					return ((char *)haystack + x);
			}
		}
		x++;
	}
	return (NULL);
}
