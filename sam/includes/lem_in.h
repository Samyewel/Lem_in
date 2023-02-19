/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:56:26 by swilliam          #+#    #+#             */
/*   Updated: 2023/02/19 14:05:48 by sam              ###   ########.fr       */
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
// ROOMS: Prints all rooms and all relevant data.
# define ROOMS 0
// PATHS: Prints all paths found from start to end.
# define PATHS 1
// GRAPH: Prints the contents of the residual graph for the BFS.
# define GRAPH 1
// SOLUTIONS: Prints the contents of a solution.
# define SOLUTIONS 1
// LINES: Prints the total amount of lines used for printing ant moves.
# define LINES 1
// LEAKS: Prints a memory leak report.
# define LEAKS 0

# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"
# include <stdbool.h>

# define INT_MAX 2147483647
# define MAX_SIZE 10000
# define MAX_ANT 10000

typedef struct data
{
	int					ant_count;
	int					room_count;
	int					path_count;
	int					longest_path;
	int					line_count;
	int					finished;
	int					ant_num;
	int					counter;
	bool				starting_search;
	bool				start_found;
	bool				ending_search;
	bool				end_found;
	bool				links_started;
	char				*last_link_0;
	char				*last_link_1;
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
	int				x;
	int				y;
	struct rooms	**links;
	struct rooms	*next;
	struct rooms	*previous;
}				t_rooms;

typedef struct paths
{
	int				nb;
	int				length;
	int				usage;
	int				temp_usage;
	int				temp;
	struct rooms	**room;
	struct paths	*next;
	struct paths	*previous;
}				t_paths;

typedef struct solutions
{
	int					nb;
	int					*path_indexes;
	int					path_count;
	int					paths_used;
	int					total_length;
	int					turns;
	struct paths		*temp_previous;
	struct paths		**path;
	struct solutions	*next;
}				t_solutions;

typedef struct ants
{
	struct rooms	**room;
	int				ant_number;
	int				index;
	int				index_end;
	struct ants		*next;
	char			*room_location;
	bool			has_moved;
	bool			has_finished;
}				t_ants;

typedef struct heads
{
	struct data			*data;
	struct rooms		**room;
	struct stack		*stack;
	struct queue		*queue;
	int					*parent;
	bool				*visited;
	int					**graph;
	int					**residual;
	struct paths		**path;
	struct solutions	**solution;
	struct ants			*ants;
}				t_heads;

typedef struct queue
{
    int				*data;
    int				head;
    int				tail;
	int				size;
}				t_queue;

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
void		print_rooms(t_heads *heads);
void		print_paths(t_paths **paths);
void		print_path(t_paths *path);
void		print_graph(t_heads *heads, int **graph);
void		print_solution(t_solutions *solution);

// Reading:
void		read_input(t_data *data, t_heads *heads);

// Rooms
t_rooms		*create_room(\
			t_data *data, t_heads *heads, t_rooms *room, char *line);
t_rooms		*store_room(\
			t_data *data, t_heads *heads, t_rooms *room, char *line);
int			find_start_room(t_heads *heads);
int			find_end_room(t_heads *heads);
t_rooms		*find_room(t_rooms **rooms, int room_id);
t_rooms		*find_room_name(t_rooms **rooms, char *name);

// Links:
void		store_link(\
			t_rooms **rooms, char *link_a, char *link_b, t_heads *heads);

// Paths:
void		create_new_path(t_heads *heads, int end);
t_paths		*get_path(t_heads *heads, int path_nb);

// Path calculation:
void		backtrack_rooms(t_data *data, t_heads *heads);
void		backtrack_paths(t_data *data, t_heads *heads);
t_paths		*shortest_path(t_data *data, t_heads *heads);

// BFS graph:
void		initialise_graphs(t_data *data, t_heads *heads);
void		populate_graph(t_data *data, t_heads *heads);
void		update_residual(int **residual, bool *visited, t_paths *path);

// Flow
void 		edmonds_karp(t_data *data, t_heads *heads);

// Queue
t_queue		*init_queue(t_heads *heads, int size);
void		enqueue(t_queue *queue, int value);
void		dequeue(t_queue *queue);
int			is_empty(t_queue *queue);

// Solutions
t_solutions	*create_solution(t_heads *heads, t_paths *path, int i);
t_solutions	*initialise_solution(t_paths *path);
void		store_solution(t_data *data, t_heads *heads);
void		calculate_usage(\
			t_data *data, t_heads *heads, t_solutions *solution);
t_solutions	**initialise_solutions(t_data *data);

// DFS
void		push(t_stack *stack, t_rooms *room, t_heads *heads);
t_node		*pop(t_stack *stack);

// Optimisation
void		room_list_to_array(t_heads *heads);
void		path_list_to_array(t_heads *heads);

// Data cleaning:
void		clean_lem_in(t_heads *heads, char *str);
void		clean_path_list(t_heads *heads);
void		clean_path_array(t_heads *heads);

// Printer
void		ant_mover(t_heads *heads, t_data *data);
void		give_rest_paths(t_ants *ants, t_paths **paths, t_data *data, int i);
void		move_played(t_ants *ants, t_data *data, t_heads *heads);
void		first_move(t_ants *ants, t_paths **paths, t_data *data, int i);
void		send_ants(t_ants *ants, t_data *data, t_paths **paths, int i);
void		move_ants_already_in_play(t_ants *ants);
t_ants		*make_ants(t_data *data, t_ants *ants, t_heads *heads);

//Errors
void		room_errors(char *line, t_data *data, t_heads *heads);
void		room_store_errors(char **line_split, t_heads *heads);
void		check_link_errors(char **line_split, t_data *data, t_heads *heads);
void		verify_rooms(t_heads *heads, t_data *data);
void		file_errors(t_heads *heads, int line_n, t_data *data);
void		start_and_end_verify(t_data *data, t_heads *heads);
void		start_and_end_errors(t_data *data, char *line, t_heads *heads);
int			ft_is_dash(char *str);
int			ft_is_space(char *str);

#endif