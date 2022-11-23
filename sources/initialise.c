/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:45:20 by swilliam          #+#    #+#             */
/*   Updated: 2022/11/21 15:12:36 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** initialise_data:
** -
*/

t_data	*initialise_data(t_data *data)
{
	if (!(data))
		data = (t_data *)malloc(sizeof(t_data));
	data->ant_count = 0;
	data->starting_search = false;
	data->ending_search = false;
	return (data);
}
