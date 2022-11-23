/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaliber <egaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 17:27:42 by egaliber          #+#    #+#             */
/*   Updated: 2022/11/23 15:17:27 by egaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

typedef struct rooms
{
	char			*name;
	int				coord_x;
	int				coord_y;
	bool			start;
	bool			end;
	int				ants;
	struct rooms	*next;
	struct rooms	*flow;
	struct links	*links;
}				t_rooms;

typedef struct s_queue
{
	struct s_rooms	*name;
	struct s_queue	*next;
}	t_queue;

void	check_links(t_queue **tail, t_queue *que)
{
	/*array of the links is needed
	need to check the flows
	*/
	t_rooms	link_array;
	int i;

	i = 0;
}

void	init_bfs(t_rooms *rooms, t_queue **head, t_queue **tail, t_queue **que)
{
	t_rooms *start; 
	
	start = find_start_room(&rooms);
	ft_printf("%d\n", start);
	*head->next = NULL;
	*tail = *head;
	*que = *head;
}

static int	bfs(t_data *data, t_rooms *rooms)
{
	t_queue	*que;
	t_queue	*tail;
	t_queue *head;

	que = NULL;
	tail = NULL;
	head = NULL;
	init_bfs(rooms, head, &tail, &que);
	/*does end have a name/room assigned to it*/
	while (rooms->end->parent == NULL) // while end doesnthave (we havent checked all)
	{
		check_links(que, tail)
		que->next;
	}
}