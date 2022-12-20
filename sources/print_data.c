/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:29:43 by swilliam          #+#    #+#             */
/*   Updated: 2022/12/20 17:29:27 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** print_data:
** - Prints all data that has been stored.
*/

void	print_data(t_data *data, t_rooms *rooms)
{
	t_rooms	*ptr;
	t_links	*link;
	t_rooms	*start;
	t_rooms	*end;

	start = find_start_room(&rooms);
	end = find_end_room(&rooms);
	ptr = rooms;
	ft_printf("\nAnt count: %d\n", data->ant_count);
	ft_printf("Starting room: %s\n", start->name);
	ft_printf("Ending room: %s\n\n", end->name);
	while (ptr)
	{
		ft_printf("Name: %s\n", ptr->name);
		ft_printf("x: %d\ny: %d\n", ptr->coord_x, ptr->coord_y);
		ft_printf("Start? %d\nEnd? %d\n", ptr->start, ptr->end);
		link = ptr->links;
		while (link)
		{
			ft_printf("Links to: %s\n", link->name);
			link = link->next;
		}
		ft_printf("\n");
		ptr = ptr->next;
	}
}

/*
** print_queue:
** - Prints the contents of the queue.
*/

void	print_queue(t_queue **queue)
{
	t_queue	*temp_queue;

	temp_queue = *queue;
	ft_printf("Queue:\n");
	while (temp_queue)
	{
		if (temp_queue->visited)
			ft_printf("!");
		ft_printf("%s", temp_queue->name);
		ft_printf(" [%d]", temp_queue->depth);
		if (!temp_queue->valid)
			ft_printf(" (INVALID)");
		if (temp_queue->next != NULL)
			ft_printf(", ");
		temp_queue = temp_queue->next;
	}
	ft_printf("\n");
}

void	print_path_name(t_queue *path_node)
{
	if (path_node->end)
		ft_printf("%s", path_node->name);
	else
		ft_printf("%s->", path_node->name);
}

void	print_paths(t_paths **path_list)
{
	t_paths	*temp_path_list;
	t_queue	*temp_path;

	temp_path_list = *path_list;
	while (temp_path_list)
	{
		ft_printf("Path[%d]: ", temp_path_list->path_nb);
		temp_path = &temp_path_list->path;
		while (temp_path)
		{
			print_path_name(temp_path);
			ft_printf("%s->", temp_path->name);
			temp_path = temp_path->next;
		}
		temp_path_list = temp_path_list->next;
	}
}
