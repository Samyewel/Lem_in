/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_printing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:29:43 by swilliam          #+#    #+#             */
/*   Updated: 2023/01/17 13:09:25 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** print_data:
** - Prints all data that has been stored.
*/

void	print_data(t_data *data)
{
	if (DEBUG == true && DATA == true)
	{
		ft_printf("\nAnt count: %d\n", data->ant_count);
		ft_printf("\nRoom count: %d\n", data->room_count);
	}
}

/*
** print_rooms:
** - Prints all stored rooms and relevant links.
*/

void	print_rooms(t_rooms **rooms)
{
	t_rooms	*ptr;
	t_links	*link;

	ptr = *rooms;
	if (DEBUG == true && ROOMS == true)
	{
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
}

/*
** print_queue:
** - Prints the contents of the queue.
*/

void	print_queue(t_queue **queue)
{
	t_queue	*temp_queue;

	temp_queue = *queue;
	if (DEBUG == true && QUEUE == true)
	{
		ft_printf("Queue:\n");
		while (temp_queue)
		{
			if (temp_queue->visited)
				ft_printf("!");
			ft_printf("%s", temp_queue->name);
			ft_printf(" [%d]", temp_queue->depth);
			if (temp_queue->next != NULL)
				ft_printf(", ");
			temp_queue = temp_queue->next;
		}
		ft_printf("\n");
	}
}

void	print_paths(t_paths **path_list)
{
	t_paths	*temp_path_list;
	t_queue	*temp_path;

	temp_path_list = *path_list;
	if (DEBUG == true && PATHS == true)
	{
		while (temp_path_list)
		{
			ft_printf("Path[%d]: ", temp_path_list->path_nb);
			temp_path = temp_path_list->path;
			while (temp_path)
			{
				if (temp_path->end)
					ft_printf("%s\n", temp_path->name);
				else
					ft_printf("%s->", temp_path->name);
				temp_path = temp_path->next;
			}
			temp_path_list = temp_path_list->next;
		}
	}
}

void	print_flows(t_queue *path)
{
	t_queue	*temp_path;

	temp_path = path;
	if (DEBUG == true && FLOWS == true)
	{
		while (temp_path)
		{
			ft_printf("%s[%d]", temp_path->name, temp_path->edge_flow);
			if (temp_path->end)
				ft_printf("\n");
			else
				ft_printf("->");
			temp_path = temp_path->next;
		}
	}
}
