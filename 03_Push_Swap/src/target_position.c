/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   target_position.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarden <alcarden@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 01:06:01 by alcarden          #+#    #+#             */
/*   Updated: 2024/03/13 01:18:46 by alcarden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../inc/push_swap.h"

// int	ft_find_target(t_stack *stack, int num, int maxint)
// {
// 	int	target;

// 	target = 0;
// 	while (stack)
// 	{
// 		if (num < stack->content && stack->content < maxint)
// 		{
// 			maxint = stack->content;
// 			target = stack->act_pos;
// 		}
// 		stack = stack->next;
// 	}
// 	return (target);
// }

// int	ft_find_min(t_stack *stack, int maxint)
// {
// 	int	target;

// 	target = 0;
// 	while (stack)
// 	{
// 		if (stack->content < maxint)
// 		{
// 			maxint = stack->content;
// 			target = stack->act_pos;
// 		}
// 		stack = stack->next;
// 	}
// 	return (target);
// }

// int	ft_get_pos(t_stack *stack_a, int num, int target, int maxint)
// {
// 	target = ft_find_target(stack_a, num, maxint);
// 	if (maxint != 2147483647)
// 		return (target);
// 	return (ft_find_min(stack_a, maxint));
// }

// t_stacks	ft_set_target(t_stacks stacks)
// {
// 	t_stack	*tmp;
// 	int		target;

// 	tmp = stacks.stack_b;
// 	while (tmp)
// 	{
// 		if (tmp->content == 2147483647)
// 			target = stacks.sizea;
// 		else
// 			target = ft_get_pos(stacks.stack_a, tmp->content, target,
// 					2147483647);
// 		tmp->targ_pos = target;
// 		tmp = tmp->next;
// 	}
// 	return (stacks);
// }
