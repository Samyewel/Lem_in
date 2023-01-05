/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_printer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaliber <egaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 14:28:29 by egaliber          #+#    #+#             */
/*   Updated: 2023/01/05 14:31:09 by egaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	move_ants_alrdy_in_play(t_result *res, t_ants *ants, t_data *data, t_queue *test)
{
	ants->room_location = ants->next_room->room_name;
	ants->next_room = ants->next_room->next;
	printf("L%d-%s", ants->ant_number, ants->room_location);
	//ants = ants->next;
}

void	send_next(t_result *res, t_ants *ants, t_data *data, t_queue *test)
{
	ants->room_location = test->room_name;
	ants->next_room = test->next;
	ft_printf("L%d-%s\n", ants->ant_number, ants->room_location);
	ants->has_moved = true;
}

void	send_first(t_result *res, t_ants *ants, t_data *data, t_queue *test)
{
	ants->room_location = test->room_name;
	ants->next_room = test->next;
	ft_printf("L%d-%s\n", ants->ant_number, ants->room_location);
	ants->has_moved = true;
}

void	printer(t_result *res, t_ants *ants, t_data *data, t_queue *test)
{
	int i;
	int x;

	i = 0;
	x = 0;
	//printf("\nwhat is i = %d\n", test->i);
	//printf("data number of ants = %d\n\n", data->number_of_ants);
	while (data->finished != data->number_of_ants)
	{
		if (ants->ant_number == 1 && ants->has_moved == false && ants->has_finished == false)
		{
			send_first(res, ants, data, queue);
		}
		if (heads->ants_head->has_moved == true)
		{
			ants = head->head_ants;
			while (ants->has_moved == true && data->finished != data->ants_count)
			{
				if (ants->has_moved == true && ants->has_finished == false)
					{
						move_ants_alrdy_in_play(res, ants, data, queue);
						//printf("|%d|", ants->ant_number);
						if  (ft_atoi(ants->room_location) == data->number_of_rooms)//== 0)
						{
							ants->has_finished = true;
							data->finished++;
							//printf("|%d|", ants->ant_number);
						}
						if (ants->ant_number == data->ant_count)
						{
							ants = heads->ants_head;
							ft_printf("\n");
						}
						else
							ants = ants->next;
					}
				else
					if (ants->ant_number == data->ant_count)
						ants = heads->ants_heads;
					else
						ants = ants->next;
			}
			
		}
		if (ants->has_moved == false && ants->has_finished == false && ants->ant_number <= data->number_of_ants)
		{
			send_next(res, ants, data, queue);
				if (ants->ant_number == data->ant_count)
					ants = heads->ants_head;
				else
					ants = ants->next;
		}
	}
}

void	ant_mover(t_paths *paths, t_queue *queue, t_heads *heads)
{
	t_ants	*ants;
	t_ants	*temp;

	while (data->ant_num < data->ant_count)
		ants = make_ants(data, ants);
	temp = heads->ants_head
	printer(ants, queue, heads, paths, data)
}
