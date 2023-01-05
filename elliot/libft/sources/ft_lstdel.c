/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 12:21:37 by sam               #+#    #+#             */
/*   Updated: 2022/08/25 19:19:48 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_lstdel:
** - Takes as a parameter the address of a pointer to a link and frees
**   the memory of this link and every successors of that link using
**   the functions del and free(3).
** - The pointer to the link that was just freed is set to NULL.
*/

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*node;
	t_list	*temp;

	if (!alst || !del)
		return ;
	node = *alst;
	while (node)
	{
		del(node->content, node->content_size);
		temp = node->next;
		free(node);
		node = temp;
	}
	*alst = NULL;
}
