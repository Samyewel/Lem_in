/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:56:26 by swilliam          #+#    #+#             */
/*   Updated: 2023/02/19 15:45:56 by sam              ###   ########.fr       */
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
# define GRAPH 0
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
	struct paths		**path;
	struct solutions	**solution;
	struct ants			*ants;
	struct queue		*queue;
	int					*parent;
	bool				*stored;
	int					**residual;
}				t_heads;

typedef struct queue
{
    int				*data;
    int				head;
    int				tail;
	int				size;
}				t_queue;

// Debugging:
void		print_rooms(t_heads *heads);
void		print_paths(t_paths **paths);
void		print_path(t_paths *path);
void		print_graph(t_heads *heads, int **graph);
void		print_solution(t_solutions *solution);

// Reading:
void		read_input(t_data *data, t_heads *heads);
void		room_errors(char *line, t_data *data);
void		room_store_errors(char **line_split);
void		check_link_errors(char **line_split, t_data *data);
void		verify_rooms(t_heads *heads, t_data *data);
void		file_errors(t_heads *heads, int line_n, t_data *data);
void		start_and_end_verify(t_data *data);
void		start_and_end_errors(t_data *data, char *line);

// Rooms
t_rooms		*create_room(\
			t_data *data, t_heads *heads, t_rooms *room, char *line);
t_rooms		*store_room(\
			t_data *data, t_heads *heads, t_rooms *room, char *line);
int			find_start_room(t_heads *heads);
int			find_end_room(t_heads *heads);
t_rooms		*find_room(t_rooms **rooms, int room_id);
t_rooms		*find_room_name(t_rooms **rooms, char *name);
void		store_link(t_rooms **rooms, char *link_a, char *link_b);

// Paths:
void		create_new_path(t_heads *heads, int end);
t_paths		*get_path(t_heads *heads, int path_nb);
t_paths		*shortest_path(t_data *data, t_heads *heads);

// Edmonds Karp functionality:
void		initialise_graphs(t_data *data, t_heads *heads);
void		populate_graph(t_data *data, t_heads *heads, int **graph);
void		update_residual(int **residual, bool *visited, t_paths *path);
void 		edmonds_karp(t_data *data, t_heads *heads);

// Queue
t_queue		*init_queue(int size);
void		enqueue(t_queue *queue, int value);
void		dequeue(t_queue *queue);
int			is_empty(t_queue *queue);

// Solution
void		backtrack_paths(t_data *data, t_heads *heads);
t_solutions	*create_solution(t_heads *heads, t_paths *path, int i);
t_solutions	*initialise_solution(t_paths *path);
void		store_solution(t_data *data, t_heads *heads);
void		calculate_usage(t_data *data, t_solutions *solution);
t_solutions	**initialise_solutions(t_data *data);

// Data cleaning:
void		clean_lem_in(char *str);

// Printer
void		move_ants(t_heads *heads, t_data *data);
void		give_rest_paths(t_ants *ants, t_paths **paths, t_data *data, int i);
void		move_played(t_ants *ants, t_data *data, t_heads *heads);
void		first_move(t_ants *ants, t_paths **paths, t_data *data, int i);
void		send_ants(t_ants *ants, t_paths **paths, int i);
void		move_ants_already_in_play(t_ants *ants);
t_ants		*make_ants(t_data *data, t_ants *ants, t_heads *heads);

int			ft_is_dash(char *str);
int			ft_is_space(char *str);

#endif