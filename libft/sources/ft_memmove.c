/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 16:25:58 by swilliam          #+#    #+#             */
/*   Updated: 2022/08/25 19:20:27 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_memmove:
** - The memmove() function copies len bytes from string src to string dst.
** - The two strings may overlap; the copy is always done in a non-destructive
**   manner.
** - Returns the original value of dst.
*/

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*copy;
	const unsigned char	*source;

	copy = (unsigned char *) dst;
	source = (const unsigned char *) src;
	if (!copy && !source)
		return (NULL);
	if ((unsigned long) copy > (unsigned long) source)
	{
		while (len-- > 0)
			copy[len] = source[len];
	}
	else
		return (ft_memcpy(dst, src, len));
	return (dst);
}
