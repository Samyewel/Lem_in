/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_int_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:53:59 by sam               #+#    #+#             */
/*   Updated: 2023/01/20 12:54:26 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_sort_int_tab(int *tab, unsigned int size)
{
	unsigned int	i;
	int				temp;
	int				swapped;

	i = 1;
	temp = 0;
	if (size == 0 || size == 1)
		return ;
	while (i < size)
	{
		swapped = 0;
		if (tab[i] < tab[i - 1] && i > 0)
		{
			temp = tab[i];
			tab[i] = tab[i - 1];
			tab[i - 1] = temp;
			i = 1;
			swapped = 1;
		}
		if (swapped == 0)
			i++;
	}
}
