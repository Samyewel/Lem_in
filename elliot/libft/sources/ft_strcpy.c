/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 11:21:54 by sam               #+#    #+#             */
/*   Updated: 2021/11/25 16:53:17 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_strcpy:
** - Copies the string src to dst (including the terminating `\0' character.)
*/

char	*ft_strcpy(char *dst, const char *src)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (src[x])
		dst[y++] = src[x++];
	dst[y] = '\0';
	return ((char *)dst);
}
