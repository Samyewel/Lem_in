/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 12:31:26 by sam               #+#    #+#             */
/*   Updated: 2022/08/25 19:19:51 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_lstdelone:
** - Takes as a parameter a link’s pointer address and frees the memory
**   of the link’s content using the function del given as a parameter
** - Then frees the link’s memory using free(3).
** - The memory of next is not freed under any circumstance.
** - The pointer to the link that was just freed must be set to NULL
*/

void	ft_lstdelone(t_list **alst, void (*del)(void *, size_t))
{
	if (alst && del)
	{
		del((*alst)->content, (*alst)->content_size);
		free(*alst);
		*alst = NULL;
	}
}
