/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarden <alcarden@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 22:43:09 by alcarden          #+#    #+#             */
/*   Updated: 2024/02/27 18:40:24 by alcarden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

int	ft_pos(int n)
{
	if (n < 0)
		return (n * -1);
	else
		return (n);
}

t_stack	*ft_cheapest(t_stack *stack_b)
{
	t_stack	*tmp;
	t_stack	*cheapest;

	tmp = stack_b;
	cheapest = tmp;
	while (tmp)
	{
		if (ft_pos(tmp->cost_a) + ft_pos(tmp->cost_b) < ft_pos(cheapest->cost_a)
			+ ft_pos(cheapest->cost_b))
			cheapest = tmp;
		tmp = tmp->next;
	}
	return (cheapest);
}

t_stacks	ft_calculate_cost(t_stacks stacks)
{
	t_stack	*tmp;

	tmp = stacks.stack_b;
	while (tmp)
	{
		tmp->cost_b = tmp->act_pos;
		if (tmp->act_pos > ft_get_size(stacks.stack_b) / 2)
			tmp->cost_b = (ft_get_size(stacks.stack_b) - tmp->act_pos) * -1;
		tmp->cost_a = tmp->targ_pos;
		if (tmp->targ_pos > ft_get_size(stacks.stack_a) / 2)
			tmp->cost_a = (ft_get_size(stacks.stack_a) - tmp->targ_pos) * -1;
		tmp = tmp->next;
	}
	return (stacks);
}
