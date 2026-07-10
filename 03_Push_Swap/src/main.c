/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarden <alcarden@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 19:41:27 by alcarden          #+#    #+#             */
/*   Updated: 2024/03/13 02:46:04 by alcarden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

// void ft_leak(void)
// {
// 	system("leaks -q push_swap");
// }

int	main(int argc, char *argv[])
{
	t_stacks	stacks;

	if (argc > 1)
	{
		stacks.stack_a = NULL;
		stacks.stack_b = NULL;
		if (ft_check_follow(argv) == 0 || ft_check_chars(argv) == 0)
			return (1);
		stacks.stack_a = ft_init_a(argc, argv, stacks.stack_a);
		ft_set_position(&stacks.stack_a);
		if (ft_error(stacks.stack_a) == 0)
			return (1);
		stacks.sizea = argc - 1;
		if (ft_is_sort(stacks.stack_a))
		{
			stacks.stack_a = ft_clean_stack(stacks.stack_a);
			return (0);
		}
		if (stacks.sizea == 3)
			stacks.stack_a = ft_sort_three(stacks.stack_a);
		else
			stacks = ft_sort(stacks);
		stacks.stack_a = ft_clean_stack(stacks.stack_a);
		return (0);
	}
}
