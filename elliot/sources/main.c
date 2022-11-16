/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaliber <egaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:16:16 by swilliam          #+#    #+#             */
/*   Updated: 2022/11/16 12:39:27 by egaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int	error_management(char *input)
{
	char	*line;
	int		fd;
	int		i;

	line = NULL;
	i = 1;
	fd = open(input[1], O_RDONLY);
	while (i > 0)
	{
		i = get_next_line(fd, &line);
		ft_printf("%s\n", line);
		ft_strdel(&line);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_rooms	*rooms;
	t_links	*links;
	t_data *data;
	int	i;

	// Maybe initiate struct function?

	rooms = (t_rooms *)malloc(sizeof(t_rooms));
	links = (t_links *)malloc(sizeof(t_links));
	data = (t_data *)malloc(sizeof(t_data));
	if (!rooms || !links)
		exit(EXIT_FAILURE);
	i = 1;
	if (argc == 2)
	{
		if (!error_management(argv[1]))
			exit(EXIT_FAILURE);
		else
		{
			ft_printf("All Gucci.\n");
			exit(EXIT_SUCCESS);
		}
	}
	else
		ft_printf("Error.\n");
	return (0);
}
