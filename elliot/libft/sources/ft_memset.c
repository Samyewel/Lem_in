/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 16:26:08 by swilliam          #+#    #+#             */
/*   Updated: 2022/08/25 19:20:30 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_memset:
** - The memset() function writes len bytes of value c
**	 (converted to an unsigned char) to the string b.
** - Returns first argument.
*/

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*edit;
	size_t			x;

	edit = (unsigned char *) b;
	x = 0;
	while (x < len)
		edit[x++] = (unsigned char) c;
	return (b);
}
