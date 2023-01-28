/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaliber <egaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:28:47 by swilliam          #+#    #+#             */
/*   Updated: 2023/01/23 15:26:08 by egaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

/*
** Debug toggles:
** - DEBUG: Enables the printing of debug messages.
** - INPUT: Prints the contents of the file being input into the program.
** - EXTRA: Prints the contents of the data struct.
** - ROOMS: Prints all rooms and all relevant data.
** - QUEUE: Prints the queue used for the BFS algorithm.
** - PATHS: Prints all paths found from start to end.
** - LEAKS: Prints a memory leak report.
*/

# define DEBUG 1
# define INPUT 0
# define EXTRA 1
# define ROOMS 0
# define QUEUE 0
# define PATHS 1
# define LEAKS 1

# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"
# include <stdbool.h>

typedef struct data
{
	int				ant_count;
	int				room_count;
	int				finished;
	int				ant_num;
	bool			starting_search;
	bool			ending_search;
}				t_data;

typedef struct rooms
{
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
	bool			valid;
	int				flow;
	int				depth;
	struct queue	*next;
	struct queue	*previous;
}				t_queue;

typedef struct paths
{
	int				path_nb;
	struct paths	*next;
	struct queue	path;
	int				temp;
}				t_paths;

typedef struct heads
{
	struct paths	*paths_head;
	struct rooms	*rooms_head;
	struct queue	*queue_head;
	struct ants		*ants_head;
}				t_heads;

	typedef struct ants
{
	struct queue			*room;
	int						ant_number;
	struct ants				*next;
	char					*room_location;
	bool					has_moved;
	bool					has_finished;
}				t_ants;

// Debugging:
void	print_data(t_data *data);
void	print_rooms(t_rooms **rooms);
void	print_queue(t_queue **queue);
void	print_path_name(t_queue *path_node);
void	print_paths(t_paths **path_list);

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
void	create_new_path(t_heads *heads, t_rooms *room);
void	store_path_data(t_heads *heads, t_rooms *room);

// BFS functionality:
int		find_max_flow(t_heads *heads);
t_paths	*backtrack_queue(t_heads *heads);

// Data cleaning:
void	clean_queue(t_queue **queue);
t_ants	*make_ants(t_data *data, t_ants *ants, t_heads *heads);

// Printer
void	ant_mover(t_paths *paths, t_queue *queue, t_heads *heads, t_data *data);
t_ants	*make_ants(t_data *data, t_ants *ants, t_heads *heads);
void	give_rest_paths(t_ants *ants, t_paths *paths, int i, t_heads *heads);
void	move_played(t_ants *ants, t_paths *paths, t_data *data, \
					t_heads *heads);

#endif