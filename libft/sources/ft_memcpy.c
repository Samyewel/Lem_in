/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 16:25:30 by swilliam          #+#    #+#             */
/*   Updated: 2022/08/25 19:20:21 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_memcpy:
** - Copies n bytes from memory area src to memory area dst.
** - If dst and src overlap, behavior is undefined.
** - Applications in which dst and src might overlap should use
**   ft_memmove instead.
*/

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*copy;
	const unsigned char	*source;
	size_t				x;

	copy = (unsigned char *) dst;
	source = (const unsigned char *) src;
	if (!copy && !source)
		return (NULL);
	if (n < 0)
		return (NULL);
	x = 0;
	while (x < n)
	{
		copy[x] = source[x];
		x++;
	}
	return (copy);
}
