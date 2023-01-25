/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table_creation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 12:40:19 by sam               #+#    #+#             */
/*   Updated: 2023/01/25 17:59:53 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** add_to_table:
** -
*/

void	add_to_table(
t_hash_table *hash_table,
t_rooms *node,
int index)
{
	unsigned int		new_index;

	if (index < 0)
		new_index = hash_function(node->name, hash_table->size);
	else
		new_index = (unsigned int)index;
	hash_table->table[new_index]->data = node;
	hash_table->table[new_index]->index = new_index;
	node->index = new_index;
}

/*
** check_node_visited:
** -
*/

static bool	check_node_visited(
t_hash_table *hash_table,
char *node_name)
{
	int					i;
	int					index;
	t_hash_node			*temp_node;

	i = 0;
	index = hash_function(node_name, hash_table->size);
	temp_node = hash_table->table[index];
	if (temp_node->data == NULL)
		return (false);
	while (i < hash_table->size)
	{
		if (hash_table->table[i]->data)
			if (ft_strcmp(temp_node->data->name, node_name) == 0)
				return (true);
		i++;
	}
	return (false);
}

/*
** initialise_hash_table:
** -
**
*/

t_hash_table	*initialise_hash_table(int size)
{
	int				i;
	t_hash_table	*hash_table;

	i = 0;
	hash_table = (t_hash_table *)malloc(sizeof(t_hash_table));
	if (!hash_table)
		return (NULL);
	hash_table->size = size;
	hash_table->table = (t_hash_node **)malloc(sizeof(t_hash_node *) * size);
	while (i < size)
	{
		hash_table->table[i] = (t_hash_node *)malloc(sizeof(t_hash_node));
		if (!hash_table->table[i])
			return (NULL);
		hash_table->table[i]->data = NULL;
		i++;
	}
	return (hash_table);
}

/*
** store_paths_in_hash_table:
** -
*/

void	store_paths_in_hash_table(t_heads *heads)
{
	t_paths			*temp_path;
	t_rooms			*temp_node;
	t_hash_table	*new_table;

	new_table = initialise_hash_table(MAX_SIZE);
	if (!new_table)
		ft_printf_strerror("Memory allocation failure in \
		store_paths_in_hash_table");
	temp_path = heads->paths;
	while (temp_path)
	{
		temp_node = temp_path->path;
		while (temp_node)
		{
			if (!check_node_visited(new_table, temp_node->name))
				add_to_table(new_table, temp_node, -1);
			temp_node = temp_node->next;
		}
		temp_path = temp_path->next;
	}
	heads->hash_table = new_table;
	rehash_table(heads, heads->hash_table);
}
