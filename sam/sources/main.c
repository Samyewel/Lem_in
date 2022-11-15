/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:16:16 by swilliam          #+#    #+#             */
/*   Updated: 2022/11/07 17:08:25 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	error_management(char **input)
{
	int	i;

	i = 1;
	while (input[i])
	{

		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_rooms	*rooms;
	t_links	*links;
	int	i;

	rooms = (t_rooms *)malloc(sizeof(t_rooms));
	links = (t_links *)malloc(sizeof(t_links));
	if (!rooms || !links)
		exit(EXIT_FAILURE);
	i = 1;
	if (argc > 1)
	{
		while (i != argc)
			ft_printf("input :%s\n", argv[i++]);
		if (!error_management(argv))
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
