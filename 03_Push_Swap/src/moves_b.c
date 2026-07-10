/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarden <alcarden@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 22:34:34 by alcarden          #+#    #+#             */
/*   Updated: 2024/02/26 22:35:00 by alcarden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

t_stack	*ft_sb(t_stack *stack_b, int flag)
{
	int	tmp;

	if (!stack_b || !stack_b->next)
		return (stack_b);
	tmp = stack_b->content;
	stack_b->content = stack_b->next->content;
	stack_b->next->content = tmp;
	if (flag)
		ft_printf("sb\n");
	ft_set_position(&stack_b);
	return (stack_b);
}

t_stacks	ft_pb(t_stacks stacks)
{
	t_stack	*tmp;

	if (stacks.stack_a)
	{
		if (!stacks.stack_b)
		{
			stacks.stack_b = stacks.stack_a;
			stacks.stack_a = stacks.stack_a->next;
			stacks.stack_b->next = NULL;
		}
		else
		{
			tmp = stacks.stack_b;
			stacks.stack_b = stacks.stack_a;
			stacks.stack_a = stacks.stack_a->next;
			stacks.stack_b->next = tmp;
		}
	}
	ft_printf("pb\n");
	ft_set_position(&stacks.stack_a);
	ft_set_position(&stacks.stack_b);
	return (stacks);
}

t_stack	*ft_rb(t_stack *stack_b, int flag)
{
	int		tmp;
	t_stack	*first;

	if (!stack_b || !stack_b->next)
		return (stack_b);
	first = stack_b;
	stack_b = stack_b->next;
	while (stack_b->next)
	{
		tmp = stack_b->content;
		stack_b->content = stack_b->next->content;
		stack_b->next->content = tmp;
		stack_b = stack_b->next;
	}
	tmp = first->content;
	first->content = stack_b->content;
	stack_b->content = tmp;
	if (flag)
		ft_printf("rb\n");
	ft_set_position(&first);
	return (first);
}

t_stack	*ft_rrb(t_stack *stack_b, int flag)
{
	t_stack	*last;
	t_stack	*first;

	if (!stack_b || !stack_b->next)
		return (stack_b);
	first = stack_b;
	while (stack_b->next->next)
		stack_b = stack_b->next;
	last = stack_b->next;
	stack_b->next = NULL;
	last->next = first;
	if (flag)
		ft_printf("rrb\n");
	ft_set_position(&last);
	return (last);
}
