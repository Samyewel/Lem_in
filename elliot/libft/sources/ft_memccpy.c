/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 16:25:01 by swilliam          #+#    #+#             */
/*   Updated: 2022/08/25 19:20:11 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_memccpy:
** - The memccpy() function copies bytes from string src to string dst.
** - If the character c (as converted to an unsigned char) occurs in the
**   string src, the copy stops and a pointer to the byte after the copy of
**   c in the string dst is returned. Otherwise, n bytes are copied, and a
**   NULL pointer is returned.
*/

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*copy;
	const unsigned char	*source;
	unsigned char		ch;
	size_t				x;

	copy = (unsigned char *) dst;
	source = (const unsigned char *) src;
	ch = c;
	x = 0;
	if (n < 0)
		return (NULL);
	while (x < n)
	{
		copy[x] = source[x];
		if (copy[x] == ch)
			return (copy + x + 1);
		x++;
	}
	return (NULL);
}
