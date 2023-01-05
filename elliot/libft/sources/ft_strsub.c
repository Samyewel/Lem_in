/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 15:13:21 by swilliam          #+#    #+#             */
/*   Updated: 2022/08/25 19:22:11 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_strsub:
** - Allocates (with malloc(3)) and returns a “fresh” substring from the
**   string given as argument.
** - The substring begins at indexstart and is of size len.
** - If start and len aren’t refer- ing to a valid substring, the behavior
**   is undefined.
** - If the allocation fails, the function returns NULL.
*/

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	x;

	if (!s)
		return (NULL);
	substring = ft_strnew(len);
	if (!substring)
		return (NULL);
	x = 0;
	if (start >= ft_strlen(s))
	{
		substring[x] = '\0';
		return (substring);
	}
	while (x < len && s[start + x])
	{
		substring[x] = s[start + x];
		x++;
	}
	return (substring);
}
