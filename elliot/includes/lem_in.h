/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:28:47 by swilliam          #+#    #+#             */
/*   Updated: 2022/11/07 17:02:20 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "ft_printf.h"
# include "libft.h"

typedef struct rooms
{
	char			*name;
	int				coord_x;
	int				coord_y;
	int				start;
	int				end;
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

#endif