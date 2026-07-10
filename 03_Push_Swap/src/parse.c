/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarden <alcarden@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 19:41:09 by alcarden          #+#    #+#             */
/*   Updated: 2024/03/13 00:37:08 by alcarden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

int	ft_max_int(t_stack *stack)
{
	t_stack	*tmp;

	tmp = stack;
	while (tmp)
	{
		if (tmp->content > 2147483647 || tmp->content < -2147483648)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int	ft_parse(t_stack *stack)
{
	t_stack	*tmp;
	t_stack	*tmp2;
	int		zero;

	tmp = stack;
	zero = 0;
	while (tmp)
	{
		tmp2 = stack->next;
		if (tmp->content == 0 || tmp->content == -0 || tmp->content == +0)
			zero++;
		while (tmp2)
		{
			if (tmp2->content == tmp->content && tmp2->act_pos != tmp->act_pos)
				return (0);
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
	if (zero > 1)
		return (0);
	return (1);
}

int	ft_error(t_stack *stack)
{
	if (ft_parse(stack) == 0)
	{
		ft_printf("[ERROR] Wrong numbers imput\n");
		stack = ft_clean_stack(stack);
		return (0);
	}
	if (ft_max_int(stack) == 0)
	{
		ft_printf("[ERROR] Higher or lower values than INT included \n");
		stack = ft_clean_stack(stack);
		return (0);
	}
	return (1);
}
