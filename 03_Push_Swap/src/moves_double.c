/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_double.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarden <alcarden@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 22:40:30 by alcarden          #+#    #+#             */
/*   Updated: 2024/03/13 00:35:50 by alcarden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

t_stacks	ft_ss(t_stacks stacks)
{
	stacks.stack_a = ft_sa(stacks.stack_a, 0);
	stacks.stack_b = ft_sa(stacks.stack_b, 0);
	ft_printf("ss\n");
	ft_set_position(&stacks.stack_a);
	ft_set_position(&stacks.stack_b);
	return (stacks);
}

t_stacks	ft_rr(t_stacks stacks)
{
	stacks.stack_a = ft_ra(stacks.stack_a, 0);
	stacks.stack_b = ft_rb(stacks.stack_b, 0);
	ft_printf("rr\n");
	ft_set_position(&stacks.stack_a);
	ft_set_position(&stacks.stack_b);
	return (stacks);
}

t_stacks	ft_rrr(t_stacks stacks)
{
	stacks.stack_a = ft_rra(stacks.stack_a, 0);
	stacks.stack_b = ft_rrb(stacks.stack_b, 0);
	ft_printf("rrr\n");
	ft_set_position(&stacks.stack_a);
	ft_set_position(&stacks.stack_b);
	return (stacks);
}
