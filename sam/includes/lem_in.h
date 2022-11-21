/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:28:47 by swilliam          #+#    #+#             */
/*   Updated: 2022/11/21 17:09:25 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"
# include <stdbool.h>

typedef struct	data
{
	int				ant_count;
	bool			starting_search;
	bool			ending_search;
}				t_data;

typedef struct rooms
{
	char			*name;
	int				coord_x;
	int				coord_y;
	bool			start;
	bool			end;
	int				ants;
	struct rooms	*next;
}				t_rooms;

typedef struct	links
{
	char			*a;
	char			*b;
	struct links	*next;
}				t_links;

/*
** Testing functions:
*/
void	print_data(t_data *data, t_rooms *rooms, t_links *links);

/*
** Initialisation:
*/
t_data	*initialise_data(t_data *data);

/*
** List utilities:
*/
t_rooms	*create_room(t_rooms *rooms);

/*
** Reading:
*/
void	read_input(t_data *data, t_rooms **rooms, t_links *links);
t_rooms	*store_room_data(t_data *data, t_rooms *rooms, char *line);

#endif