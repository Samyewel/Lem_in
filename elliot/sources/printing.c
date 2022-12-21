/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaliber <egaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 12:07:23 by egaliber          #+#    #+#             */
/*   Updated: 2022/12/21 11:25:52 by egaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

typedef struct needed
{
	//number of paths
	//number ants (which struct is this in)
	//struct "option where there are paths"
	//paths in list in option->path1
	//number of rooms
	// max usage of a path
	
};

typedef struct s_data
{
	t_ants			*head_ants;
	int				num;
	int				ant_count;
	bool			starting_search;
	bool			ending_search;
	int				ants_finished;
	int				ant_num;
	
} t_data;

typedef struct paths
{
	char			*name;
	struct paths	*next;
}				t_paths;

typedef struct ants
{
	t_paths	*paths;
	int	ant_number;
	t_ants	*next;
}	t_ants;

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

typedef struct s_result
{
	int		finished;
	int		ant_number;
	size_t	moves;
	size_t	left;
}	t_result;

/* TEST PART 

void	init_testing(t_testing *new)
{
	new->i = 0;
	new->next = NULL;
}

t_testing	*make_new(t_data *data, t_testing *new, int i)
{
	new = (t_testing *)malloc(sizeof(t_testing));
	init_testing(new);
	new->i = i;
	return (new);
}

t_testing	*make_test(int i, t_data *data, t_testing *test)
{
	t_testing	*new;
	
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

	data has head of ants
	(options = diffrent paths) inside paths -> rooms

 ENDS HERE */

void	check_if_end(t_result *res, t_ants *ants, t_data *data)
{
	if (ants->ant_number = )
}

void	send_first(t_rooms *rooms, t_result *res, t_ants *ants, t_data *data)
{
	int i;

	i = 0;
	while (i < data->paths_amount)
	{
		if ()
		{
			res->left += 1;
			ants->ant_number = ants->paths->name;
			check_if_end(res, ants, data);
		}
	}
}

void	print_moves(t_rooms *rooms, t_result *res, t_ants *ants, t_data *data)
{
	while (res->finished != rooms->ants)
	{
		res->ant_number = 0;
		while (ants->ant_number < rooms->ants)
		{
			if (ants->ant_number == 1)//rooms->start)
				send_first(rooms, res, ants, data);
		}
	}
}

void	init_ants(t_ants *new)
{
	new->ant_number = 0;
	new->next = NULL;
	new->paths = NULL;
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

void	init_res_and_ants(t_result *res, t_ants *ants, t_rooms *rooms, t_data *data)
{
	res->ant_number = 0;
	res->moves = 0;
	res->left = 0;
	res->finished = 0;
	
	data->ant_num = 0; // initialize in the beginning
	data->head_ants = NULL; // initialize in the beginning
	
	while (res->ant_number < rooms->ants)
	{
		ants = make_ants(data, ants);
		res->ant_number = rooms->start;
		res->ant_number++;
		(t_ants *)malloc(sizeof(t_ants) * rooms->ants);
	}	
}

void	printer(t_rooms *rooms, t_paths *paths, t_ants *ants, t_data *data)
{
	t_ants		*ants;
	t_result	*res;
	t_paths		paths_count;

	init_res_and_ants(res, ants, rooms, data);
	print_moves(rooms, res, ants, data);
	
}


// How can print out the whole node
int	main()
{
	t_data	*data;
	t_testing *test;
	t_testing *temp;
	int i;
	int x;

	i = 1;
	x = 0;
	data = (t_data *)malloc(sizeof(t_data));
	init_data(data);
	while (i < 10)
	{
		test = make_test(i, data, test);
		i++;
	}
	temp = data->head;
	while (temp)
	{
		printf("\n num; %i", temp->i);
		temp = temp->next;
	}
	printf("\n");
}