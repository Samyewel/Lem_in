/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:17:48 by sam               #+#    #+#             */
/*   Updated: 2022/08/25 19:20:03 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	del(void *content, size_t content_size)
{
	free(content);
	(void)content_size;
}

/*
** ft_lstmap:
** - Iterates a list 'lst' and applies the function 'f' to each link to
**   create a “fresh” list (using malloc(3)) resulting from the successive
**   applications of f.
** - If the allocation fails, the function returns NULL.
*/

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new_lst;
	t_list	*new;

	if (lst == NULL || f == NULL)
		return (NULL);
	new_lst = f(lst);
	if (!new_lst)
		return (NULL);
	new = new_lst;
	lst = lst->next;
	while (lst)
	{
		new->next = f(lst);
		if (!new->next)
		{
			ft_lstdel(&new_lst, &del);
			return (NULL);
		}
		new = new->next;
		lst = lst->next;
	}
	new->next = NULL;
	return (new_lst);
}
