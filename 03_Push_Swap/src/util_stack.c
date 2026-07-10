/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarden <alcarden@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 22:21:32 by alcarden          #+#    #+#             */
/*   Updated: 2024/03/13 02:42:42 by alcarden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

t_stack	*ft_init_a(int size, char **numbers, t_stack *stack_a)
{
	int		cnt;
	t_stack	*first;

	cnt = 1;
	if (size == 2)
		return (ft_init_a2(ft_split(numbers[1], ' '), stack_a));
	first = malloc(sizeof(t_stack));
	first->content = ft_atol(numbers[cnt]);
	first->act_pos = 0;
	first->next = malloc(sizeof(t_stack));
	stack_a = first->next;
	cnt++;
	while (cnt < size - 1)
	{
		stack_a->content = ft_atol(numbers[cnt]);
		stack_a->next = malloc(sizeof(t_stack));
		stack_a = stack_a->next;
		cnt++;
	}
	stack_a->content = ft_atol(numbers[cnt]);
	stack_a->next = NULL;
	return (first);
}

t_stack	*ft_init_a2(char **numbers, t_stack *stack_a)
{
	int		cnt;
	int		size;
	t_stack	*first;

	cnt = 0;
	size = ft_split_size(numbers);
	first = malloc(sizeof(t_stack));
	first->content = ft_atol(numbers[cnt]);
	first->act_pos = 0;
	first->next = malloc(sizeof(t_stack));
	stack_a = first->next;
	cnt++;
	if (size == 1)
		return (ft_clean(first, numbers));
	while (cnt < size - 1)
	{
		stack_a->content = ft_atol(numbers[cnt]);
		stack_a->next = malloc(sizeof(t_stack));
		stack_a = stack_a->next;
		cnt++;
	}
	stack_a->content = ft_atol(numbers[cnt]);
	stack_a->next = NULL;
	ft_free_str(numbers);
	return (first);
}

int	ft_is_sort(t_stack *stack)
{
	t_stack	*tmp;

	tmp = stack;
	while (tmp)
	{
		if (tmp->next && tmp->content > tmp->next->content)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}
