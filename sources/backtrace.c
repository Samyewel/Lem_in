/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtrace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:28:33 by swilliam          #+#    #+#             */
/*   Updated: 2022/12/09 19:21:38 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** is_valid:
** -
*/

int		is_valid(t_queue **queue, char *parent_name, char *link_name)
{
	t_queue	*temp_queue;

	temp_queue = NULL;
	temp_queue = *queue;
	if (ft_strcmp(parent_name, link_name) == 0)
		return (0);
	while (temp_queue)
	{
		if (ft_strcmp(temp_queue->name, parent_name) == 0)
			return (temp_queue->valid);
		temp_queue = temp_queue->next;
	}
	return (0);
}

/*
** find_depth:
** -
*/

int		find_depth(t_queue **queue, char *room_name)
{
	t_queue	*temp_queue;

	temp_queue = *queue;
	while (temp_queue)
	{
		if (ft_strcmp(temp_queue->name, room_name) == 0)
			return (temp_queue->depth);
		temp_queue = temp_queue->next;
	}
	return (-1);
}

/*
** trace_path:
** -
*/

void	trace_path(t_queue *queue, t_rooms *rooms, t_rooms *parent, char *link)
{
	t_rooms	*temp_room;
	t_links	*temp_links;
	int		paths;

	paths = 0;
	if (parent->start || !is_valid(&queue, parent->name, link))
		return ;
	ft_printf("%s->", parent->name);
	temp_room = find_room(&rooms, link);
	temp_links = temp_room->links;
	while (temp_links)
	{
		if (is_valid(&queue, parent->name, temp_links->name) && find_depth(&queue, parent->name) >= find_depth(&queue, temp_links->name))
			trace_path(queue, rooms, temp_room, temp_links->name);
		temp_links = temp_links->next;
	}
}

/*
** backtrace_queue:
** -
*/
// !start, !1, !6, !8, !2, !12, !7, !9, !3, !4, !10, !end, !11, !5
// #        12     4 - 5
// #         |    /     \
// # start - 1 - 2 - 3 - end
// #    | \     /    |
// #    |  6 - 7     |
// #    |            |
// #    8 - 9 - 10 - 11
// PATH [1] = start -> 1 -> 2 -> 4 -> 5 -> end
// PATH [2] = start -> 8 -> 9 -> 10 -> 11 -> 3 -> end

t_queue	*backtrace_queue(t_queue *queue, t_rooms **room_head, t_rooms *rooms)
{
	t_queue	*result;
	t_rooms	*end_room;
	t_links	*temp_links;

	end_room = find_end_room(room_head);
	temp_links = end_room->links;
	result = NULL; //create_queue_node(result, temp_room->name);
	while (temp_links)
	{
		ft_printf("\n\nTRACING NEXT END_ROOM LINK\n");
		trace_path(queue, rooms, end_room, temp_links->name);
		temp_links = temp_links->next;
	}
	return (result);
}
