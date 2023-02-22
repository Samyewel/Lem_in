/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:56:26 by swilliam          #+#    #+#             */
/*   Updated: 2023/02/22 14:54:31 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

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
	int					line_count;
	int					finished;
	int					ant_num;
	int					counter;
	int					bfs_path;
	bool				starting_search;
	bool				start_found;
	bool				ending_search;
	bool				end_found;
	bool				links_started;
	bool				lines;
	bool				print_paths;
	char				**input;
	char				*last_link_0;
	char				*last_link_1;
	struct solutions	*solution;
}				t_data;

typedef struct flags
{
	bool		input;
	bool		ants;
	bool		rooms;
	bool		paths;
	bool		graph;
	bool		solutions;
	bool		lines;
}				t_flags;

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
	int				bfs_index;
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
	struct flags		*flags;
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
	int					*data;
	int					head;
	int					tail;
	int					size;
}				t_queue;

// Flags:
void		set_flags(t_flags *flags, char flag);
void		parse_flags(t_flags *flags, int argc, char **argv);

// Debugging:
void		print_rooms(t_heads *heads);
void		print_paths(t_heads *heads, t_paths **paths);
void		print_path(t_heads *heads, t_paths *path);
void		print_graph(t_heads *heads, int **graph);
void		print_solution(t_heads *heads, t_solutions *solution);

// Reading:
void		read_input(t_data *data, t_heads *heads);
void		room_errors(char *line, t_data *data);
void		room_store_errors(char **line_split);
void		check_link_errors(char **line_split, t_data *data);
void		verify_rooms(t_heads *heads, t_data *data);
void		file_errors(t_heads *heads, int line_n, t_data *data);
void		start_and_end_verify(t_data *data);
void		start_and_end_errors(t_data *data, char *line);

// Input printing:
void		store_input(t_data *data, char *line, int line_n);
void		print_input(t_heads *heads, t_data *data);

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
void		initialise_edmonds_karp(t_data *data, t_heads *heads);
void		initialise_graph(t_data *data, t_heads *heads);
void		populate_graph(t_data *data, t_heads *heads, int **graph);
void		update_visited(bool *visited, t_paths *path);
void		edmonds_karp(t_data *data, t_heads *heads);
int			continue_bfs(t_heads *heads, int *parent, bool *stored);

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
void		calculate_path_use(t_data *data, t_solutions *solution, \
			int path_count);
t_solutions	**initialise_solutions(t_data *data);

// Data cleaning:
void		clean_lem_in(char *str);

// Printer
void		printer(t_heads *heads, t_data *data);
void		give_rest_paths(t_ants *ants, t_paths **paths, int i);
void		move_played(t_ants *ants, t_data *data, t_heads *heads);
void		first_move(t_heads *heads, t_ants *ants, t_paths **paths, int i);
void		send_ants(t_heads *heads, t_ants *ants, t_paths **paths, int i);
void		move_ants_already_in_play(t_heads *heads, t_ants *ants);
t_ants		*make_ants(t_data *data, t_ants *ants, t_heads *heads);
void		only_start_end(t_heads *heads, t_ants *ants);

// Utilities
int			ft_is_dash(char *str);

#endif