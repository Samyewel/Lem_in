/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 15:12:50 by swilliam          #+#    #+#             */
/*   Updated: 2022/08/25 19:20:08 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_memalloc:
** - Allocates (with malloc(3)) and returns a “fresh” memory area.
** - The memory allocated is initialized to 0.
** - If the allocation fails, the function returns NULL.
*/

void	*ft_memalloc(size_t size)
{
	void	*fresh;

	if (!size)
		return (NULL);
	fresh = (void *) malloc(size);
	if (!(fresh))
		return (NULL);
	ft_bzero(fresh, size);
	return (fresh);
}
