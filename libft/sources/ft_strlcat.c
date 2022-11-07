/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 12:22:14 by sam               #+#    #+#             */
/*   Updated: 2022/08/25 19:21:26 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_strlcat:
** - Appends string src to the end of dst.
** - It will append at most dstsize - strlen(dst) - 1 characters.
** - It will then NUL-terminate, unless dstsize is 0 or the original dst
**   string was longer than dstsize (in practice this should not happen as
**   it means that either dstsize is incorrect or that dst is not a proper
**   string).
*/

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	x;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	x = 0;
	if (dstsize <= 0 || dst_len > dstsize)
		return (src_len + dstsize);
	else
	{
		while (src[x] != '\0' && (dst_len + x) < dstsize)
		{
			dst[dst_len + x] = src[x];
			x++;
		}
		if ((dst_len + x) == dstsize && dst_len < dstsize)
			dst[dst_len + x - 1] = '\0';
		else
			dst[dst_len + x] = '\0';
		return (dst_len + src_len);
	}
}
