/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 20:30:16 by sam               #+#    #+#             */
/*   Updated: 2023/01/25 18:22:11 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** clean_queue:
** - Flushes the contents of the queue.
*/

void	clean_path_nodes(t_rooms **nodes)
{
	t_rooms	*temp_node;
	t_rooms	*temp_data;

	temp_node = *nodes;
	while (temp_node)
	{
		temp_data = temp_node->next;
		ft_strdel(&temp_node->name);
		free(temp_node);
		temp_node = temp_data;
	}
}

void	clean_paths(t_heads *heads)
{
	t_paths	*current_path;
	t_paths	*next_path;

	current_path = heads->paths;
	next_path = NULL;
	while (current_path != NULL)
	{
		next_path = current_path->next;
		clean_path_nodes(&current_path->path);
		free(current_path);
		current_path = next_path;
	}
	heads->paths = NULL;
}

void	clean_hash_table(t_hash_table *hash_table)
{
	int	i;

	i = -1;
	while (++i < hash_table->size)
		free(hash_table->table[i]);
	free(hash_table->table);
	free(hash_table);
}

void	clean_adjacency_matrix(int **graph, int rows)
{
	int	y;

	y = 0;
	while (y < rows)
	{
		free(graph[y]);
		y++;
	}
	free(graph);
}
