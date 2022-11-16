/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:16:16 by swilliam          #+#    #+#             */
/*   Updated: 2022/11/16 16:43:49 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** lem-in:
** -
*/

int	main(void)
{
	t_data	*data;
	t_rooms	*rooms;
	t_links	*links;

	rooms = (t_rooms *)malloc(sizeof(t_rooms));
	links = (t_links *)malloc(sizeof(t_links));
	data = (t_data *)malloc(sizeof(t_data));
	if (!rooms || !links || !data)
		exit(EXIT_FAILURE);
	initialise_structs(data, rooms, links);
	read_input(data, rooms, links);
	print_data(data, rooms, links); //for testing purposes
	exit(EXIT_SUCCESS);
	return (0);
}
