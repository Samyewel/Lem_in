/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:28:47 by swilliam          #+#    #+#             */
/*   Updated: 2023/01/25 18:58:39 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

/*
** Debug toggles:
*/
// DEBUG: Enables the printing of debug messages.
# define DEBUG 1
// INPUT: Prints the contents of the file being input into the program.
# define INPUT 0
// EXTRA: Prints the contents of the data struct.
# define DATA 0
// ROOMS: Prints all rooms and all relevant data.
# define ROOMS 0
// QUEUE: Prints the queue used for the BFS algorithm.
# define QUEUE 0
// PATHS: Prints all paths found from start to end.
# define PATHS 1
// FLOWS: Prints the flows during each iteration of the Edmonds Karp process.
# define FLOWS 0
// HASH: Prints the contents of the paths stored in the hash table.
# define HASH 1
// LEAKS: Prints a memory leak report.
# define LEAKS 1

# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"
# include <stdbool.h>

# define MAX_SIZE 1024
# define INT_MAX 2147483647
# define INT_MIN -2147483648

typedef struct data
{
	int				ant_count;
	int				room_count;
	int				longest_path;
	int				max_flow;
	int				finished;
	int				ant_num;
	bool			starting_search;
	bool			ending_search;
}				t_data;

typedef struct rooms
{
	int				id;
	unsigned int	index;
	char			*name;
	bool			start;
	bool			end;
	bool			visited;
	int				is_room;
	int				ants;
	int				coord_x;
	int				coord_y;
	struct links	*links;
	struct rooms	*next;
	struct rooms	*previous;
}				t_rooms;

typedef struct links
{
	char			*name;
	struct links	*next;
}				t_links;

typedef struct paths
{
	int				path_nb;
	int				path_flow;
	struct rooms	*path;
	struct paths	*next;
}				t_paths;

typedef struct queue
{
    int				*data;
    int				head;
    int				tail;
}				t_queue;

typedef struct hash_node
{
	t_rooms				*data;
	unsigned int		index;
}				t_hash_node;

typedef struct hash_table
{
	t_hash_node	**table;
	int			size;
}				t_hash_table;

typedef struct ants
{
	struct queue	*next_room;
	int				ant_number;
	struct ants		*next;
	char			*room_location;
	bool			has_moved;
	bool			has_finished;
}				t_ants;

typedef struct heads
{
	struct rooms		*rooms;
	struct stack		*stack;
	struct hash_table	*hash_table;
	struct queue		*queue;
	struct paths		*paths;
	struct ants			*ants;
}				t_heads;

# define MAX_NAME_LENGTH 100

typedef struct stack_node
{
	int					id;
	char				name[MAX_NAME_LENGTH];
	int					flow;
	bool				start;
	bool				end;
	struct stack_node	*next;
}	t_node;

typedef struct stack
{
	struct stack_node	*nodes;
	int					top;
}				t_stack;

// Debugging:
void	print_data(t_data *data);
void	print_rooms(t_rooms **rooms);
void	print_queue(t_queue *queue, int size);
void	print_paths(t_paths **path_list);
void	print_hash_table(t_hash_table *hash_table);
void	print_graph(t_heads *heads, int **graph, int rows, int columns);

// Initialisation:
t_data	*initialise_data(t_data *data);
t_heads	*initialise_heads(t_heads *heads);

// Reading:
void	read_input(t_data *data, t_heads *heads);

// Rooms
t_rooms	*create_room(t_rooms *rooms);
t_rooms	*store_room_data(t_data *data, t_rooms *rooms, char *line);
t_rooms	*find_start_room(t_rooms **rooms);
t_rooms	*find_end_room(t_rooms **rooms);
t_rooms	*find_room(t_rooms **rooms, char *link_name);

// Links:
t_links	*store_link(t_rooms **rooms, char *link_a, char *link_b);

// Queue:
t_queue	*init_queue(int size);
int		is_empty(t_queue *queue);
void	dequeue(t_queue *queue);
void	enqueue(t_queue *queue, int size, int value);
// t_queue	*create_queue(t_queue *queue, char *room, t_queue *prev);
// int		is_empty(t_queue **queue);
// t_rooms	*visit_next(t_queue **queue, t_rooms **rooms);
// void	explore_room(t_queue **queue_head, t_queue *queue, t_rooms *room);
// void	reset_visted(t_queue **queue);

// Paths:
void	create_new_path(t_heads *heads, t_node *start_node);
void	store_path_data(t_heads *heads, t_node *node);

// Max flow calculation:
void	calculate_flow(t_heads *heads, t_data *data);
void	backtrack(t_heads *heads, t_data *data);
t_queue	*bfs_confirm_path(t_rooms **rooms);
int	bfs(t_heads *heads, int **graph, int start, int end);

//DFS
void	push(t_stack *stack, t_rooms *room);
t_node	*pop(t_stack *stack);

//Hash table
void	store_paths_in_hash_table(t_heads *heads);
t_hash_table	*initialise_hash_table(int size);
void	add_to_table(t_hash_table *hash_table, t_rooms *node, int index);
unsigned int	hash_function(char *str, int size);
void	rehash_table(t_heads *heads, t_hash_table *hash_table);
int	get_index(t_hash_table *hash_table, char *name);


// Data cleaning:
void	clean_path_nodes(t_rooms **nodes);
void	clean_paths(t_heads *heads);
void	clean_hash_table(t_hash_table *hash_table);
void	clean_adjacency_matrix(int **graph, int rows);

#endif