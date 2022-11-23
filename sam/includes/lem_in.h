/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:28:47 by swilliam          #+#    #+#             */
/*   Updated: 2022/11/23 16:02:10 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

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
	int				coord_x;
	int				coord_y;
	bool			start;
	bool			end;
	int				ants;
	struct rooms	*next;
	struct links	*links;
}				t_rooms;

/*
** Remove before submission.
** Testing functions:
*/
void	print_data(t_data *data, t_rooms *rooms);

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

#endif