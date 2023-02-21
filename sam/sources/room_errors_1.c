/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   room_errors_1.c									:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: swilliam <swilliam@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/02/06 12:50:45 by egaliber		  #+#	#+#			 */
/*   Updated: 2023/02/20 16:14:53 by swilliam		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "lem_in.h"

/*
** start_and_end_errors:
** - Edge cases for when an error is met.
*/

void	start_and_end_errors(t_data *data, char *line)
{
	if (data->start_found == true && data->starting_search == true)
		clean_lem_in("Error in start/end node.");
	if (ft_strlen(line) != 5 && ft_strlen(line) != 7)
		clean_lem_in("Error in start/end node.");
	if (data->ending_search == true)
		clean_lem_in("Error in start/end node.");
	if (data->start_found == true && data->end_found == true)
		clean_lem_in("Error in start/end node.");
}

/*
** start_and_end_verify:
** - Edge cases for when an error is met.
*/

void	start_and_end_verify(t_data *data)
{
	if (data->starting_search && data->ending_search)
		clean_lem_in("Error in start/end node.");
}

/*
** verify_rooms:
** - Edge cases for when an error is met.
*/

void	verify_rooms(t_heads *heads, t_data *data)
{
	int		counter;
	int		i;

	i = -1;
	counter = 0;
	while (++i < data->room_count)
	{
		if (ft_strcmp(heads->room[i]->name, heads->room[i + 1]->name) == 0)
			clean_lem_in("Duplicate room names.");
		if (heads->room[i]->start == true || heads->room[i]->end == true)
			counter++;
	}
	if (data->ending_search == true || data->starting_search)
		clean_lem_in("No start found.");
}

/*
** file_errors:
** - Used when input has been read, ensuring there are no failures met.
*/

void	file_errors(t_heads *heads, int line_n, t_data *data)
{
	int	i;

	i = -1;
	if (line_n == 0)
		clean_lem_in("Empty file.");
	if (heads->room == NULL)
		clean_lem_in("Error in file.");
	if (data->links_started == false)
		clean_lem_in("No links.");
	if (data->start_found == false || data->end_found == false)
		clean_lem_in("Error in start/end node.");
	if (data->end_found == false)
		clean_lem_in("Error in start/end node.");
	while (++i < data->room_count)
	{
		if (heads->room[i]->end == true)
		{
			if (heads->room[i]->links == NULL)
				clean_lem_in("No links to end.");
		}
	}
}
