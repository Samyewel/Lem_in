/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtrack_queue.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:28:33 by swilliam          #+#    #+#             */
/*   Updated: 2022/12/20 17:06:02 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** find_depth:
** -
*/

static int	find_depth(t_queue **queue, char *room_name)
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
//

static int	is_valid(
t_queue **queue,
t_rooms *parent,
t_rooms *current,
char *link_name)
{
	t_queue	*temp_queue;

	temp_queue = NULL;
	temp_queue = *queue;
	if (parent->start || current->end \
		|| ft_strcmp(parent->name, link_name) == 0)
		return (0);
	while (temp_queue)
	{
		if (ft_strcmp(temp_queue->name, current->name) == 0 \
			&& find_depth(queue, current->name) >= find_depth(queue, link_name))
			return (temp_queue->valid);
		temp_queue = temp_queue->next;
	}
	return (0);
}

/*
** add_to_front:
** -
*/

//t_paths add_to_paths(**path_head, t_rooms *parent, t_rooms *child)

/*
** trace_path:
** -
*/

static int	trace_path(
t_paths *paths,
t_queue *queue,
t_rooms *rooms,
t_rooms *parent,
char *link
)
{
	t_rooms	*temp_room;
	t_links	*temp_links;

	temp_room = NULL;
	temp_links = NULL;
	temp_room = find_room(&rooms, link);
	if (!is_valid(&queue, parent, temp_room, link))
		return (0);
	if (temp_room->start)
	{
		create_new_path(&paths, temp_room);
		return (1);
	}
	temp_links = temp_room->links;
	while (temp_links)
	{
		if (trace_path(paths, queue, rooms, temp_room, temp_links->name))
		{
			add_to_path(&paths, temp_room);
			return (1);
		}
		temp_links = temp_links->next;
	}
	return (parent->end);
}

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

/*
** backtrace_queue:
** -
*/

t_queue	*backtrace_queue(t_queue *queue, t_rooms **room_head, t_rooms *rooms)
{
	t_queue	*result;
	t_rooms	*end_room;
	t_links	*temp_links;
	t_paths	*paths;

	paths = NULL;
	end_room = find_end_room(room_head);
	temp_links = end_room->links;
	result = NULL;
	while (temp_links)
	{
		if (trace_path(paths, queue, rooms, end_room, temp_links->name))
			add_to_path(&paths, end_room);
		temp_links = temp_links->next;
	}
	if (DEBUG == true)
		print_paths(&paths);
	return (result);
}
