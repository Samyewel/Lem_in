/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaliber <egaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 12:35:23 by egaliber          #+#    #+#             */
/*   Updated: 2023/01/04 12:32:39 by egaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct s_paths
{
	//struct t_queue		*next;
	int					path_usage_times;
	struct s_paths		*next;
	struct s_queue		*head;
	
}	t_paths;


typedef struct s_result
{
	int		finished;
	int		ant_number;
	//size_t	moves;
	//size_t	left;
}	t_result;

typedef struct s_ants
{
	struct s_queue			*next_room;
	int						ant_number;
	struct	s_ants			*next;
	char					*room_location;
	bool					has_moved;
	bool					has_finished;
}	t_ants;


typedef struct s_queue
{
	int 				i;
	char				*room_name;
	struct s_queue		*next;
	struct s_queue		*head;
}	t_queue;

typedef struct s_data
{
	t_paths				*head2;
	t_queue				*head;
	t_ants				*head_ants;
	int					ant_num;
	int					number_of_ants;
	int					number_of_rooms;
}	t_data;

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
	printf("L%d-%s\n", ants->ant_number, ants->room_location);
	ants->has_moved = true;
}

void	send_first(t_result *res, t_ants *ants, t_data *data, t_queue *test)
{
	ants->room_location = test->room_name;
	ants->next_room = test->next;
	printf("L%d-%s\n", ants->ant_number, ants->room_location);
	ants->has_moved = true;
}

void	printer(t_result *res, t_ants *ants, t_data *data, t_queue *test)
{
	int i;
	int x;

	i = 0;
	x = 0;
	printf("\nwhat is i = %d\n", test->i);
	printf("data number of ants = %d\n\n", data->number_of_ants);
	while (res->finished != data->number_of_ants)
	{
		if (ants->ant_number == 1 && ants->has_moved == false && ants->has_finished == false)
		{
			send_first(res, ants, data, test);
		}
		if (data->head_ants->has_moved == true)
		{
			ants = data->head_ants;
			while (ants->has_moved == true && res->finished != data->number_of_ants)
			{
				if (ants->has_moved == true && ants->has_finished == false)
					{
						move_ants_alrdy_in_play(res, ants, data, test);
						//printf("|%d|", ants->ant_number);
						if  (ft_atoi(ants->room_location) == data->number_of_rooms)//== 0)
						{
							ants->has_finished = true;
							res->finished++;
							//printf("|%d|", ants->ant_number);
						}
						if (ants->ant_number == data->number_of_ants)
						{
							ants = data->head_ants;
							printf("\n");
						}
						else
							ants = ants->next;
					}
				else
					if (ants->ant_number == data->number_of_ants)
						ants = data->head_ants;
					else
						ants = ants->next;
			}
			
		}
		if (ants->has_moved == false && ants->has_finished == false && ants->ant_number <= data->number_of_ants)
		{
			send_next(res, ants, data, test);
				if (ants->ant_number == data->number_of_ants)
					ants = data->head_ants;
				else
					ants = ants->next;
		}
	}
}

void	init_testing(t_queue *new)
{
	new->i = 0;
	new->next = NULL;
	new->room_name = NULL;
}

t_queue	*make_new(t_data *data, t_queue *new, int i)
{
	new = (t_queue *)malloc(sizeof(t_queue));
	init_testing(new);
	new->i = i;
	new->room_name = ft_itoa(i);
	return (new);
}

t_queue	*make_test(int i, t_data *data, t_queue *test)
{
	t_queue	*new;
	
	new = make_new(data, new, i);
	if (data->head == NULL)
	{
		test = new;
		data->head = new;
	}
	else
	{
		test->next = new;
		test = test->next;
	}
	return (test);
}
/*	data has head of ants
	(options = diffrent paths) inside paths -> rooms
*/

void	init_ants(t_ants *new)
{
	new->ant_number = 0;
	new->next = NULL;
	new->next_room = NULL;
	new->has_moved = false;
	new->room_location = NULL;
	new->has_finished = false;
}

t_ants	*make_new_ant(t_data *data, t_ants *new)
{
	new = (t_ants *)malloc(sizeof(t_ants));
	init_ants(new);
	data->ant_num++;
	new->ant_number = data->ant_num;
	return (new);
}

t_ants	*make_ants(t_data *data, t_ants *ants)
{
	t_ants	*new_ant;
	
	new_ant = make_new_ant(data, new_ant);
	if (data->head_ants == NULL)
	{
		ants = new_ant;
		data->head_ants = new_ant;
	}
	else
	{
		ants->next = new_ant;
		ants = ants->next;
	}
	return (ants);
}

/*t_ants	*init_res_and_ants(t_result *res, t_ants *ants, t_data *data)
{
	//res->finished = 0;
	//res->ant_number = 0;
	ants = make_ants(data, ants);
	//res->ant_number = rooms->start;
	ants->ant_number++;
	//(t_ants *)malloc(sizeof(t_ants) * data->number_of_ants);
	return(ants);
}
*/
void	init_res(t_result *res)
{
	res->ant_number = 0;
	res->finished = 0;
}

void	init_data(t_data *data)
{
	data->head2 = NULL;
	data->head_ants = NULL;
	data->head = NULL;
	data->ant_num = 0;
	data->number_of_ants = 10;
	data->number_of_rooms = 5;
	
}
void	init_paths(t_paths *paths)
{
	
}

int	main()
{
	t_data		*data;
	t_queue 	*test;
	t_queue 	*temp;
	t_result	*res;
	t_ants		*ants;
	t_ants		*temp2;
	t_paths		*paths;
	
	int i;
	int x;

	i = 1;
	x = 1;
	data = (t_data *)malloc(sizeof(t_data));
	res = (t_result *)malloc(sizeof(t_result));
	init_data(data);
	init_res(res);
	//init_paths(paths);
	// another while(1 < 3)
	while (i < 6)
	{
		test = make_test(i, data, test);
		i++;
	}
	/*
	while (x < 6)
	{
		test2 = make_test(x, data, test);
		x++;
	}
	
	temp3 = data->head;
	while (temp3)
	{
		printf("room: %i\n", temp->i);
		temp3 = temp->next;
	}
	*/
	while (data->ant_num < data->number_of_ants)
	{
		ants = make_ants(data, ants);
		//ants->ant_number++;
	}
	/*
	temp2 = data->head_ants;
	while (temp2)
	{
		printf("ants: %i\n", temp2->ant_number);
		temp2 = temp2->next;
	}
	printf("\n");
	*/
	temp2 = data->head_ants;
	temp = data->head;
	ants = temp2;
	test = temp;
	printf("ant number before printer = %d\n", ants->ant_number);
	printf("ant number before printer = %d\n", ants->next->ant_number);
	printf("room name before printer = %s\n", test->room_name);
	printer(res, ants, data, test);
	return (0);
}