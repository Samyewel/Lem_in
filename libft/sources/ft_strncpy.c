/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:18:41 by sam               #+#    #+#             */
/*   Updated: 2022/08/25 19:21:44 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_strncpy:
** - Copies at most len characters from src into dst.
** - If src is less than len characters long, the remainder of dst is filled
**   with `\0' characters. Otherwise, dst is not terminated.
*/

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	x;
	char	*destination;

	x = 0;
	destination = dst;
	if (dst == NULL && src == NULL)
		return (NULL);
	if (len < 0)
		return (NULL);
	while (x < len && src[x] != '\0')
	{
		dst[x] = src[x];
		x++;
	}
	if (x == len)
		return (destination);
	else
	{
		while (x < len)
		{
			dst[x] = '\0';
			x++;
		}
	}
	return (destination);
}
