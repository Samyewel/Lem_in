/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmonds_karp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:51:24 by sam               #+#    #+#             */
/*   Updated: 2022/11/29 15:00:07 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** bfs:
** -
*/

bool	bfs(t_rooms **rooms)
{
	bool	end_visited;
	t_rooms	*temp_room;
	t_queue	*queue;
	t_queue	*temp_queue;

	end_visited = false;
	queue = NULL;
	temp_room = find_start_room(rooms); // Points to starting room
	queue = create_queue_node(queue, temp_room->name);
	// Head of queue is given allocated a node
	if (!queue)
		ft_printf_strerror("Memory allocation failure in bfs");
	temp_queue = queue; // Points to head of queue
	if (temp_room->links == NULL)
		ft_printf_strerror("No links from start");
	while (!is_empty(&queue)) // while queue still have rooms to visit
	{
		explore_room(&queue, temp_queue, temp_room);
		// adds room links to queue
		end_visited += (temp_room->end && temp_queue->visited);
		// ensures a path from start to end exists
		temp_room = visit_next(&queue, rooms);
		// sets the room pointer to the next unvisited room in the queue
		temp_queue = temp_queue->next;
		// moves along the queue to the next room name
	}
	if (end_visited && DEBUG == true)
		print_queue(&queue); // Print contents of queue
	clean_queue(&queue); // Flush contents of queue
	return (end_visited); // Returns true if a path from start to end is found
}

/*
** edmonds_karp:
** -
*/

int	edmonds_karp(t_rooms **rooms)
{
	int	max_flow;
	int	test_toggle = 1; //set to 0 for looping, 1 for one iteration.

	max_flow = 420;
	if (test_toggle == 0)
	{
		while (bfs(rooms))
		{
			ft_printf("");
		}
	}
	else
		if (bfs(rooms))
			ft_printf("");
	return (max_flow);
}
