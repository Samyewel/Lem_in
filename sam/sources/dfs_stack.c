/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs_stack.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaliber <egaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:54:12 by swilliam          #+#    #+#             */
/*   Updated: 2023/02/09 16:21:14 by egaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_node	*create_stack_node(t_rooms *room, t_heads *heads)
{
	struct stack_node	*node;

	node = NULL;
	node = (struct stack_node *) malloc(sizeof(struct stack_node));
	if (!node)
		clean_lem_in(heads, "Memory allocation failure in push.");
	node->id = room->id;
	ft_strcpy(node->name, room->name);
	node->start = room->start;
	node->end = room->end;
	node->next = NULL;
	return (node);
}

void	push(t_stack *stack, t_rooms *room, t_heads *heads)
{
	struct stack_node	*temp_node;

	temp_node = create_stack_node(room, heads);
	if (stack->top == 0)
		stack->nodes = temp_node;
	else
	{
		temp_node->next = stack->nodes;
		stack->nodes = temp_node;
	}
	stack->top++;
}

t_node	*pop(t_stack *stack)
{
	struct stack_node	*temp_node;

	temp_node = NULL;
	if (stack->nodes != NULL)
	{
		temp_node = stack->nodes;
		stack->nodes = stack->nodes->next;
		stack->top--;
		free(temp_node);
	}
	return (temp_node);
}
