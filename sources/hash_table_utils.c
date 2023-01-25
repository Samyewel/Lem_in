/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:04:06 by sam               #+#    #+#             */
/*   Updated: 2023/01/25 18:00:10 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** get_index:
** - Loops through the hash table to return the index of the searched
**   item.
*/

int	get_index(t_hash_table *hash_table, char *name)
{
	int	i;

	i = 0;
	while (i < hash_table->size)
	{
		if (hash_table->table[i]->data)
		{
			if (ft_strcmp(hash_table->table[i]->data->name, name) == 0)
				return ((int) hash_table->table[i]->index);
		}
		i++;
	}
	return (-1);
}

/*
** hash_function:
** - Uses the djb2 algorithm by Dan Bernstein to assign a unique
**   index for storing the item in a hash table.
*/

unsigned int	hash_function(char *str, int size)
{
	unsigned int	hash;
	int				c;

	hash = 5381;
	c = 0;
	while (*str)
	{
		c = *str++;
		hash = ((hash << 5) + hash) + c;
	}
	return (hash % size);
}

/*
** count_unique_nodes:
** - Counts the amount of nodes stored within the hash table so that
**   rehashing the table is accurate.
*/

int	count_unique_nodes(t_hash_table *hash_table)
{
	int			i;
	int			count;
	t_hash_node	*temp_node;

	i = 0;
	count = 0;
	while (i < hash_table->size)
	{
		temp_node = hash_table->table[i];
		if (temp_node->data != NULL)
			count++;
		i++;
	}
	return (count);
}

/*
** rehash_table:
** - Takes a hash table and replaces it with a new one with no empty spaces.
*/

void	rehash_table(t_heads *heads, t_hash_table *hash_table)
{
	int				i;
	unsigned int	index;
	int				size;
	t_hash_table	*new_table;

	i = 0;
	index = 0;
	size = count_unique_nodes(hash_table);
	if (size >= hash_table->size)
		return ;
	new_table = initialise_hash_table(size);
	if (!new_table)
		ft_printf_strerror("Memory allocation failure in rehash_table.");
	while (i < heads->hash_table->size)
	{
		if (heads->hash_table->table[i]->data)
			add_to_table(new_table, heads->hash_table->table[i]->data, index++);
		i++;
	}
	clean_hash_table(heads->hash_table);
	heads->hash_table = new_table;
}
