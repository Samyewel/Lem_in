/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaliber <egaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 17:27:42 by egaliber          #+#    #+#             */
/*   Updated: 2022/11/23 13:09:48 by egaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

typedef struct s_queue
{
	struct s_rooms	*name;
	struct s_queue	*next;
}	t_queue;

void	init_bfs(t_rooms *rooms, t_queue **head, t_queue **tail, t_queue **que)
{
	*head = (t_queue *)malloc(sizeof(t_queue));
	if (!*head)
		error();
	(*head)->room = rooms->start;
	(*head)->next = NULL;
	*tail = *head;
	*que = *head;
}

static int	bfs(t_data *data, t_queue **head, t_rooms *rooms)
{
	t_queue	*que;
	t_queue	*tail;

	que = NULL;
	tail = NULL;
	bfs_init(rooms, head, &tail, &que);
	while (rooms->end->parent == NULL) // while end doesnthave (we havent checked all)
	{
		check_links()
	}
}