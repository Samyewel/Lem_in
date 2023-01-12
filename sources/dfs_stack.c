/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs_stack.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:54:12 by swilliam          #+#    #+#             */
/*   Updated: 2023/01/12 20:19:03 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void display_stack(t_stack stack)
{
    int i;

    i = 0;
    ft_printf("Stack contents: ");
    while (i < stack.top)
    {
        ft_printf("%s ", stack.nodes[i].name);
        i++;
    }
    ft_printf("\n");
}

void	push(t_stack *stack, t_rooms *room)
{
    struct stack_node *node;

    node = (struct stack_node *) malloc(sizeof(struct stack_node));
    if (!node)
        ft_printf_strerror("Memory allocation failure in push.");
    node->id = room->id;
    ft_strcpy(node->name, room->name);
    node->next = NULL;
    if (stack->top == 0)
        stack->nodes = node;
    else
    {
        node->next = stack->nodes;
        stack->nodes = node;
    }
    stack->top++;
    display_stack(*stack);
}

void	pop(t_stack *stack)
{
    struct stack_node  *temp_node;

    temp_node = NULL;
    if (stack->nodes != NULL && stack->top > 0)
    {
        temp_node = stack->nodes;
        stack->nodes = stack->nodes->next;
        free(temp_node);
        stack->top--;
    }
}
