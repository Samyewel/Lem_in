/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtrace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:28:33 by swilliam          #+#    #+#             */
/*   Updated: 2022/12/08 18:42:30 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** trace_path:
** -
*/

void	trace_path(t_rooms *rooms, t_rooms *parent_room, char *link_name)
{
	t_rooms	*temp_room;
	t_links	*temp_links;

	if (ft_strcmp(parent_room->name, link_name) == 0 || parent_room->start)
		return ;
	temp_room = find_room(&rooms, link_name);
	temp_links = temp_room->links;
	ft_printf("Tracing path: %s->%s\n", parent_room->name, temp_room->name);
	while (temp_links)
	{
		if (ft_strcmp(parent_room->name, temp_links->name) != 0)
			trace_path(rooms, temp_room, temp_links->name);
		temp_links = temp_links->next;
	}
}

/*
** backtrace_queue:
** -
*/
// !start, !1, !6, !8, !2, !12, !7, !9, !3, !4, !10, !end, !11, !5
// PATH [1] = start -> 1 -> 2 -> 4 -> 5 -> end
// PATH [2] = start -> 8 -> 9 -> 10 -> 11 -> 3 -> end

t_queue	*backtrace_queue(t_queue **queue, t_rooms **room_head, t_rooms *rooms)
{
	t_queue	*temp_queue;
	t_queue	*result;
	t_rooms	*end_room;
	t_links	*temp_links;

	temp_queue = *queue;
	end_room = find_end_room(room_head);
	temp_links = end_room->links;
	result = NULL; //create_queue_node(result, temp_room->name);
	while (!temp_queue->end && temp_queue->next)
		temp_queue = temp_queue->next;
	while (temp_links)
	{
		ft_printf("Tracing path: %s->%s\n", end_room->name, temp_links->name);
		trace_path(rooms, end_room, temp_links->name);
		ft_printf("\n\n\nTRACING NEXT END_ROOM LINK\n");
		temp_links = temp_links->next;
	}
	return (result);
}
