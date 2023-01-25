/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_printing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:29:43 by swilliam          #+#    #+#             */
/*   Updated: 2023/01/25 18:46:21 by sam              ###   ########.fr       */
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

void	print_paths(t_paths **path_list)
{
	t_paths	*temp_path_list;
	t_rooms	*temp_path;

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

void	print_hash_table(t_hash_table *hash_table)
{
	int			i;
	t_hash_node	*temp_node;

	i = 0;
	if (DEBUG == true && HASH == true)
	{
		ft_printf("Hash table[%d]\n", hash_table->size);
		while (i < hash_table->size)
		{
			ft_printf("[%d] ", i);
			temp_node = hash_table->table[i];
			if (temp_node->data)
				ft_printf("%s", temp_node->data->name);
			ft_printf("\n");
			i++;
		}
	}
}

void	print_graph(t_heads *heads, int **graph, int rows, int columns)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	ft_printf("   ");
	while (x < columns)
	{
		if (heads->hash_table->table[x]->data)
			ft_printf("%3.3s", heads->hash_table->table[x]->data->name);
		else
			ft_printf("%3.3c", ' ');
		x++;
	}
	ft_printf("\n");
	while (y < rows)
	{
		x = 0;
		if (heads->hash_table->table[y]->data)
			ft_printf("%3.3s", heads->hash_table->table[y]->data->name);
		else
			ft_printf("   ");
		while (x < columns)
			ft_printf("%3d", graph[y][x++]);
		ft_printf("\n");
		y++;
	}
}

void	print_queue(t_queue *queue, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		ft_printf("[%d]%d\n", i, queue->data[i]);
		i++;
	}
	ft_printf("\n");
}