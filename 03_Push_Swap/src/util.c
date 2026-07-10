/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarden <alcarden@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 22:19:12 by alcarden          #+#    #+#             */
/*   Updated: 2024/03/13 00:37:33 by alcarden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

int	ft_check_follow(char **argv)
{
	int	cnt;
	int	cnt2;

	cnt = 1;
	while (argv[cnt])
	{
		cnt2 = 0;
		while (argv[cnt][cnt2])
		{
			if (argv[cnt][cnt2] == '-' || argv[cnt][cnt2] == '+')
			{
				if (ft_isdigit(argv[cnt][cnt2 - 1]) || (argv[cnt][cnt2
						+ 1] == ' ' || argv[cnt][cnt2 + 1] == '\0')
					|| (argv[cnt][cnt2 + 1] == '-' || argv[cnt][cnt2
						+ 1] == '+'))
				{
					ft_printf("Error: Número/s con caracteres invalidos\n");
					return (0);
				}
			}
			cnt2++;
		}
		cnt++;
	}
	return (1);
}

int	ft_check_chars(char **argv)
{
	int	cnt;
	int	cnt2;

	cnt = 1;
	while (argv[cnt])
	{
		cnt2 = 0;
		while (argv[cnt][cnt2])
		{
			if (!ft_isdigit(argv[cnt][cnt2]))
			{
				if (argv[cnt][cnt2] != '-' && argv[cnt][cnt2] != '+')
				{
					if (argv[cnt][cnt2] != ' ')
					{
						ft_printf("Error: caracteres no númericos\n");
						return (0);
					}
				}
			}
			cnt2++;
		}
		cnt++;
	}
	return (1);
}

void	ft_set_position(t_stack **stack)
{
	int		cnt;
	t_stack	*tmp;

	cnt = 0;
	tmp = *stack;
	while (tmp)
	{
		tmp->act_pos = cnt;
		cnt++;
		tmp = tmp->next;
	}
}

int	ft_get_size(t_stack *stack)
{
	int	cnt;

	cnt = 0;
	while (stack)
	{
		cnt++;
		stack = stack->next;
	}
	return (cnt);
}

t_stacks	ft_sort_two(t_stacks stacks)
{
	if (stacks.stack_a->content > stacks.stack_a->next->content)
		stacks.stack_a = ft_sa(stacks.stack_a, 1);
	return (stacks);
}
