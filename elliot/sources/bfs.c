/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaliber <egaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 17:27:42 by egaliber          #+#    #+#             */
/*   Updated: 2022/11/22 17:51:10 by egaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

typedef struct s_queue
{
	struct s_rooms	*room;
	struct s_queue	*next;
}	t_queue;

void	init_bfs(t_data *data, t_queue **head, t_queue **tail)
{
	*head = (t_queue *)malloc(sizeof(t_queue));
	if (!*head)
		error();
	(*head)->room = room->start;
	(*head)->next = NULL;
	*tail = *head;
}

static int	bfs(t_data *data, t_queue **head, t_rooms *rooms)
{
	t_queue	*que;
	t_queue	*tail;

	que = NULL;
	tail = NULL;
	bfs_init(data, head, &tail, &que);
	while (rooms->end->parent == NULL) // while end doesnthave (we havent checked all)
	{
		check_links()
	}
}