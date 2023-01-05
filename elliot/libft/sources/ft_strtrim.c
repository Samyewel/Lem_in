/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 15:13:24 by swilliam          #+#    #+#             */
/*   Updated: 2022/08/25 19:22:14 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ws_start:
** - Locates whitespace characters at the beginning of the string.
*/

static size_t	ws_start(char const *s)
{
	size_t	x;

	x = 0;
	if (ft_iswhitespace(s[0]) == 1)
		while (ft_iswhitespace(s[x]) == 1)
			x++;
	return (x);
}

/*
** ws_end:
** - Locates whitespace characters at the end of the string.
*/

static size_t	ws_end(char const *s)
{
	size_t	x;
	size_t	len;

	len = ft_strlen(s);
	x = 0;
	if (ft_iswhitespace(s[len - 1]) == 1)
	{
		len = len - 1;
		while (ft_iswhitespace(s[len]) == 1)
		{
			if (len == 0)
				return (ft_strlen(s));
			x++;
			len--;
		}
	}
	return (x);
}

/*
** ft_strtrim:
** - Allocates (with malloc(3)) and returns a copy of the string given as
**   argument without whitespaces at the beginning or at the end of the string.
** - If s has no whitespaces at the beginning or at the end, the function
**   returns a copy of s.
** - If the allocation fails the function returns NULL.
*/

char	*ft_strtrim(char const *s)
{
	size_t	x;
	size_t	whitespace_start;
	size_t	whitespace_end;
	size_t	len;
	char	*trim;

	x = -1;
	if (!s)
		return (NULL);
	whitespace_start = ws_start(s);
	whitespace_end = ws_end(s);
	len = ft_strlen(s);
	if (whitespace_start == 0 && whitespace_end == 0)
		return (ft_strdup(s));
	if (whitespace_end == ft_strlen(s))
		return (ft_strdup(""));
	trim = ft_strnew(len - whitespace_start - whitespace_end);
	if (trim)
	{
		while (++x < len - whitespace_start - whitespace_end)
			trim[x] = s[x + whitespace_start];
		trim[x] = '\0';
		return (trim);
	}
	return (NULL);
}
