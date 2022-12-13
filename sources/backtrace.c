/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtrace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:28:33 by swilliam          #+#    #+#             */
/*   Updated: 2022/12/13 15:57:30 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
** is_valid:
** -
*/

// A room is valid IF:
// - It has more than one link

// 4->3->2->0
// ------2->5
// 		 ^


int		is_valid(t_queue **queue, t_rooms *room, char *link_name)
{
	t_queue	*temp_queue;

	temp_queue = NULL;
	temp_queue = *queue;
	if (ft_strcmp(room->name, link_name) == 0)
		return (0);
	if (find_depth(queue, parent_name) <= find_depth(queue, link_name))
		return (0);
	while (temp_queue)
	{
		if (ft_strcmp(temp_queue->name, link_name) == 0)
			return (temp_queue->valid);
		temp_queue = temp_queue->next;
	}
	return (0);
}

void	print_path_name(t_rooms *parent, t_rooms *link)
{
	if (parent->end)
		ft_printf("%s->", parent->name);
	ft_printf("%s", link->name);
	if (!link->start)
		ft_printf("->");

}

/*
** trace_path:
** -
*/

int		trace_path(t_queue *queue, t_rooms *rooms, t_rooms *parent, char *link)
{
	t_rooms	*temp_room;
	t_links	*temp_links;

	temp_room = NULL;
	temp_links = NULL;
	if (parent->start || !is_valid(&queue, parent->name, link))
		return (0);
	temp_room = find_room(&rooms, link);
	print_path_name(parent, temp_room);
	if (temp_room->start)
		return (1);
	temp_links = temp_room->links;
	while (temp_links)
	{
		if (is_valid(&queue, temp_room, temp_links->name))
			if (trace_path(queue, rooms, temp_room, temp_links->name))
				ft_printf("\n");
		temp_links = temp_links->next;
	}
	return (parent->end);
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
		if (trace_path(queue, rooms, end_room, temp_links->name))
			ft_printf("Start found.\n");
		temp_links = temp_links->next;
	}
	return (result);
}
