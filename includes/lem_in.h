/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:28:47 by swilliam          #+#    #+#             */
/*   Updated: 2022/12/20 16:34:00 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# define DEBUG 0 // Set to 1 if you wish to see debug messages.

# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"
# include <stdbool.h>

typedef struct data
{
	int				ant_count;
	bool			starting_search;
	bool			ending_search;
}				t_data;

typedef struct links
{
	char			*name;
	struct links	*next;
}				t_links;

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

typedef struct queue
{
	char			*name;
	bool			start;
	bool			end;
	bool			visited;
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
}				t_paths;

/*
** Testing functions:
*/
void	print_data(t_data *data, t_rooms *rooms);
void	print_queue(t_queue **queue);
void	print_path_name(t_queue *path_node);
void	print_paths(t_paths **path_list);

/*
** Initialisation:
*/
t_data	*initialise_data(t_data *data);

/*
** List creation:
*/
t_rooms	*create_room(t_rooms *rooms);
t_links	*add_link(t_rooms **rooms, char *link_a, char *link_b);

/*
** List utilities:
*/
t_rooms	*find_start_room(t_rooms **rooms);
t_rooms	*find_end_room(t_rooms **rooms);
t_rooms	*find_room(t_rooms **rooms, char *link_name);

/*
** Reading:
*/
void	read_input(t_data *data, t_rooms **rooms);
t_rooms	*store_room_data(t_data *data, t_rooms *rooms, char *line);

/*
** Queue functions:
*/
t_queue	*add_to_queue(t_queue *queue, char *room, t_queue *prev, int depth);
t_rooms	*visit_next(t_queue **queue, t_rooms **rooms);
int		is_empty(t_queue **queue);
void	explore_room(t_queue **queue_head, t_queue *queue, t_rooms *room);

/*
** BFS functionality:
*/
int		find_max_flow(t_rooms *rooms);
t_queue	*backtrace_queue(t_queue *queue, t_rooms **room_head, t_rooms *rooms);
void	add_to_path(t_paths **paths, t_rooms *room);
void	create_new_path(t_paths **paths, t_rooms *room);

/*
** Data cleaning:
*/
void	clean_queue(t_queue **queue);

#endif