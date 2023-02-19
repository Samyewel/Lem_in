/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_grid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 19:55:11 by sam               #+#    #+#             */
/*   Updated: 2023/02/19 15:18:00 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_make_grid:
** - Creates a matrix of integers with the given x and y values.
*/

int	**ft_make_grid(int rows, int columns)
{
	int	**grid;
	int	y;
	int	x;

	grid = (int **)malloc(sizeof(int *) * rows);
	if (!grid)
		return (NULL);
	y = -1;
	while (++y < rows)
	{
		grid[y] = (int *)malloc(sizeof(int) * columns);
		if (!grid[y])
			return (NULL);
		x = 0;
		while (x < columns)
		{
			grid[y][x] = 0;
			x++;
		}
	}
	return (grid);
}
