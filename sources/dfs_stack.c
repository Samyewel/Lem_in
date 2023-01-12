/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs_stack.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:54:12 by swilliam          #+#    #+#             */
/*   Updated: 2023/01/12 16:01:24 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	push(t_stack *stack, t_rooms *room)
{
    if (stack->top < MAX_STACK_SIZE)
	{
        stack->data[stack->top] = *room;
        stack->top++;
    } else {
        // Stack overflow
    }
}

void	pop(t_stack *stack)
{
    if (stack->top > 0)
	{
        stack->top--;
    }
	else
	{
        // Stack underflow
    }
}

t_rooms *peek(t_stack *stack)
{
    if (stack->top > 0)
	{
        return (&stack->data[stack->top - 1]);
    }
	else
	{
        return (NULL);
    }
}
