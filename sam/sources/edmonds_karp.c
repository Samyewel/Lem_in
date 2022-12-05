/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmonds_karp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:51:24 by sam               #+#    #+#             */
/*   Updated: 2022/12/05 16:35:23 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** bfs:
** -
*/

static bool	bfs(t_rooms **rooms)
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
		// checks to ensure end is reached
		if (end_visited)
			break ;
		// ensures a path from start to end exists
		temp_room = visit_next(&queue, rooms);
		// sets the room pointer to the next unvisited room in the queue
		temp_queue = temp_queue->next;
		// moves along the queue to the next room name
	}
	if (DEBUG == true)
		print_queue(&queue); // Print contents of queue
	clean_queue(&queue); // Flush contents of queue
	return (end_visited); // Returns true if a path from start to end is found
}

/*
** edmonds_karp:
** -
*/

static int	edmonds_karp(t_rooms **rooms)
{
	//t_queue	*paths;
	int	flow;

	//paths = NULL;
	flow = 0;
	while (bfs(rooms))
	{
		if (flow == 1) // Prevent infinite loop until functional
			break ;
		flow++;
		//save paths here
	}
	return (flow);
}

int	find_max_flow(t_rooms **rooms)
{
	int	max_flow;

	max_flow = edmonds_karp(rooms);
	if (max_flow <= 0)
	{
		return (0);
	}
	return (1);
}
