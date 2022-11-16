/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:28:47 by swilliam          #+#    #+#             */
/*   Updated: 2022/11/16 16:07:02 by swilliam         ###   ########.fr       */
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
}				t_data;

typedef struct rooms
{
	char			*name;
	int				coord_x;
	int				coord_y;
	int				start;
	bool			start_searching;
	int				end;
	bool			end_searching;
	struct rooms	*next;
	struct rooms	*previous;
}				t_rooms;

typedef struct	links
{
	char			*a;
	char			*b;
	struct links	*next;
	struct links	*previous;
}				t_links;

/*
** Initialisation:
*/
void	initialise_structs(t_data *data, t_rooms *rooms, t_links *links);

/*
** Reading:
*/
void	read_input(t_data *data, t_rooms *rooms, t_links *links);

#endif