/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:28:47 by swilliam          #+#    #+#             */
/*   Updated: 2023/01/17 13:32:12 by sam              ###   ########.fr       */
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
# define PATHS 0
// FLOWS: Prints the flows during each iteration of the Edmonds Karp process.
# define FLOWS 1
// LEAKS: Prints a memory leak report.
# define LEAKS 1

# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"
# include <stdbool.h>

# define INT_MAX 2147483647
# define INT_MIN -2147483648

typedef struct data
{
	int				ant_count;
	int				room_count;
	int				max_flow;
	int				finished;
	int				ant_num;
	bool			starting_search;
	bool			ending_search;
}				t_data;

typedef struct rooms
{
	int				id;
	char			*name;
	bool			start;
	bool			end;
	int				ants;
	int				coord_x;
	int				coord_y;
	struct links	*links;
	struct rooms	*next;
}				t_rooms;

typedef struct links
{
	char			*name;
	struct links	*next;
}				t_links;

typedef struct queue
{
	char			*name;
	bool			start;
	bool			end;
	bool			visited;
	bool			checked;
	int				depth;
	int				edge_flow;
	int				capacity;
	struct queue	*next;
	struct queue	*previous;
}				t_queue;

typedef struct paths
{
	int				path_nb;
	int				path_flow;
	struct queue	*path;
	struct paths	*next;
}				t_paths;

typedef struct heads
{
	struct paths	*paths_head;
	struct rooms	*rooms_head;
	struct queue	*queue_head;
	struct ants		*ants_head;
	struct stack	*stack;
}				t_heads;

typedef struct ants
{
	struct queue	*next_room;
	int				ant_number;
	struct ants		*next;
	char			*room_location;
	bool			has_moved;
	bool			has_finished;
}				t_ants;

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
void	print_queue(t_queue **queue);
void	print_paths(t_paths **path_list);
void	print_flows(t_queue *path);

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
t_queue	*create_queue(t_queue *queue, char *room, t_queue *prev, int depth);
int		is_empty(t_queue **queue);
t_rooms	*visit_next(t_queue **queue, t_rooms **rooms);
void	explore_room(t_queue **queue_head, t_queue *queue, t_rooms *room);
void	reset_visted(t_queue **queue);

// Paths:
void	create_new_path(t_heads *heads, t_node *start_node);
void	store_path_data(t_heads *heads, t_node *node);

// Max flow calculation:
int		calculate_flow(t_heads *heads, t_data *data);
void	backtrack_queue(t_heads *heads, t_data *data);

//DFS
void	push(t_stack *stack, t_rooms *room);
t_node	*pop(t_stack *stack);

// Data cleaning:
void	clean_queue(t_queue **queue);
void	clean_paths(t_heads *heads);

#endif