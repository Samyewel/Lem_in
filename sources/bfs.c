/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaliber <egaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:51:24 by sam               #+#    #+#             */
/*   Updated: 2022/11/28 14:31:53 by egaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

typedef struct s_queue
{
	struct s_rooms	*name;
	struct s_queue	*next;
	bool	checked;
}	t_queue;

void	check_links(t_rooms *room, t_queue *que)
{
	/*array of the links is needed
	need to check the flows
	*/
	t_links	*temp;
	t_rooms	link_array;
	temp = room;
	int i;

	i = 0;
	que->name
	que->next = find_links()

	
}

t_queue	*add_to_que(t_queue *que)
{
	que = (t_queue *)malloc(sizeof(t_queue));
	que->name = NULL;
	que->next = NULL;
	que->checked = FALSE;
	return (que);
}

void	init_bfs(t_rooms *rooms, t_queue **head, t_queue **tail, t_queue **que)
{
	t_rooms *start;
	t_rooms *end;
	
	start = find_start_room(&rooms);
	end = find_end_room(&rooms);
	ft_printf("%d\n", start);
	*head->next = NULL;
	*tail = *head;
	*que = *head;
}

static int	bfs(t_rooms *rooms)
{
	t_queue	*que;
	t_queue	*tail;
	t_queue *head;

	que = NULL;
	tail = NULL;
	head = NULL;
	init_bfs(rooms, head, &tail, &que);
	/*does end have a name/room assigned to it*/
	while (rooms->end == NULL) // while end doesnthave (we havent checked all)
	{
		check_links(que, tail)
		que = que->next;
	}
}