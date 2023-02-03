/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:56:26 by swilliam          #+#    #+#             */
/*   Updated: 2023/02/03 11:56:29 by swilliam         ###   ########.fr       */
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
// PATHS: Prints all paths found from start to end.
# define PATHS 1
// SOLUTIONS:
# define SOLUTIONS 1
// LEAKS: Prints a memory leak report.
# define LEAKS 1

# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"
# include <stdbool.h>

# define INT_MAX 2147483647
# define MAX_SIZE 1024

typedef struct data
{
	int					ant_count;
	int					room_count;
	int					longest_path;
	int					best_solution;
	int					finished;
	int					ant_num;
	int					counter;
	bool				starting_search;
	bool				ending_search;
	struct solutions	*solution;
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
	int				nb;
	int				length;
	int				usage_times;
	int				temp;
	struct rooms	*path;
	struct paths	*next;
	struct paths	*previous;
}				t_paths;

typedef struct solutions
{
	int					nb;
	int					*path_indexes;
	int					path_count;
	int					total_length;
	struct paths		*temp_previous;
	struct paths		*paths;
	struct solutions	*next;
}				t_solutions;

typedef struct ants
{
	struct rooms	*room;
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
	struct paths		*paths;
	struct solutions	*solutions;
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
void		print_data(t_data *data);
void		print_rooms(t_rooms **rooms);
void		print_paths(t_paths **path_list);
void		print_solutions(t_heads *heads);

// Initialisation:
t_data		*initialise_data(t_data *data);
t_heads		*initialise_heads(t_heads *heads);

// Reading:
void		read_input(t_data *data, t_heads *heads);

// Rooms
t_rooms		*create_room(t_rooms *rooms);
t_rooms		*store_room_data(t_data *data, t_rooms *rooms, char *line);
t_rooms		*find_start_room(t_rooms **rooms);
t_rooms		*find_end_room(t_rooms **rooms);
t_rooms		*find_room(t_rooms **rooms, char *link_name);

// Links:
t_links		*store_link(t_rooms **rooms, char *link_a, char *link_b);

// Paths:
void		create_new_path(t_heads *heads, t_node *start_node);
void		store_path_data(t_heads *heads, t_node *node);

// Path calculation:
void		calculate_flow(t_heads *heads, t_data *data);
void		backtrack_rooms(t_heads *heads, t_data *data);
void		backtrack_paths(t_heads *heads);

// Solutions
t_solutions	*initialise_solution(t_paths *path);
void		store_solution(t_heads *heads, t_data *data);
void		calculate_path_usage_times(t_data *data);

// DFS
void		push(t_stack *stack, t_rooms *room);
t_node		*pop(t_stack *stack);

// Data cleaning:
void		clean_path_nodes(t_rooms **nodes);
void		clean_paths(t_heads *heads);

// Printer
void		ant_mover(t_heads *heads, t_data *data);
void		give_rest_paths(
				t_ants *ants, t_paths *paths, t_data *data);
void		move_played(t_ants *ants, t_data *data, t_heads *heads);
void		first_move(
				t_ants *ants, t_paths *paths, t_data *data);
void		send_ants(t_ants *ants, t_data *data, t_paths *paths);
void		move_ants_already_in_play(t_ants *ants);
t_ants		*make_ants(t_data *data, t_ants *ants, t_heads *heads);

#endif