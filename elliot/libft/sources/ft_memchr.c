/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 16:25:14 by swilliam          #+#    #+#             */
/*   Updated: 2022/08/25 19:20:15 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_memchr:
** - Locates the first occurrence of c (converted to an unsigned char)
**   in string s.
** - Returns a pointer to the byte located, or NULL if no such byte exists
**   within n bytes.
*/

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*found;
	unsigned char		tofind;
	size_t				x;

	found = (const unsigned char *) s;
	tofind = (unsigned char) c;
	x = 0;
	while (x < n)
	{
		if (found[x] == tofind)
			return ((void *) found + x);
		x++;
	}
	return (NULL);
}
