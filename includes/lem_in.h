/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:28:47 by swilliam          #+#    #+#             */
/*   Updated: 2022/12/05 14:50:37 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# define DEBUG 1 // Set to 1 if you wish to see debug messages.

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
	bool			visited;
	struct queue	*next;
}				t_queue;

/*
** Testing functions:
*/
void	print_data(t_data *data, t_rooms *rooms);
void	print_queue(t_queue **queue);

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
t_queue	*create_queue_node(t_queue *queue, char *room_name);
t_rooms	*visit_next(t_queue **queue, t_rooms **rooms);
int		is_empty(t_queue **queue);
int		is_duplicate(t_queue **queue, char *link_name);
void	explore_room(t_queue **queue, t_queue *queue_node, t_rooms *room);

/*
** BFS functionality:
*/
int		find_max_flow(t_rooms **rooms);

/*
** Data cleaning:
*/
void	clean_queue(t_queue **queue);

#endif