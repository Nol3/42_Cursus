/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarden <alcarden@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 12:02:18 by alcarden          #+#    #+#             */
/*   Updated: 2024/03/13 02:46:58 by alcarden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include "../include/inc/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>

typedef struct s_stack
{
	long int		content;
	int				act_pos;
	int				targ_pos;
	int				cost_a;
	int				cost_b;
	struct s_stack	*next;
}					t_stack;

typedef struct s_stacks
{
	t_stack			*stack_a;
	t_stack			*stack_b;
	int				sizea;
	int				sizeb;
}					t_stacks;

//cases.c
int			is_case_1(int n, int m, int l);
int			is_case_2(int n, int m, int l);
int			is_case_3(int n, int m, int l);
int			is_case_4(int n, int m, int l);
int			is_case_5(int n, int m, int l);

//clean.c
char		**ft_free_str(char **str);
int			ft_split_size(char **str);
t_stack		*ft_clean(t_stack *stack, char **nums);
t_stack		*ft_clean_stack(t_stack *stack);

//cost.c
int			ft_pos(int n);
t_stack		*ft_cheapest(t_stack *stack_b);
t_stacks	ft_calculate_cost(t_stacks stacks);

//moves_a.c
t_stack		*ft_sa(t_stack *stack_a, int flag);
t_stacks	ft_pa(t_stacks stacks);
t_stack		*ft_ra(t_stack *stack_a, int flag);
t_stack		*ft_rra(t_stack *stack_a, int flag);

//moves_b.c
t_stack		*ft_sb(t_stack *stack_b, int flag);
t_stacks	ft_pb(t_stacks stacks);
t_stack		*ft_rb(t_stack *stack_b, int flag);
t_stack		*ft_rrb(t_stack *stack_b, int flag);

//moves_doubles.c
t_stacks	ft_ss(t_stacks stacks);
t_stacks	ft_rr(t_stacks stacks);
t_stacks	ft_rrr(t_stacks stacks);

//parse.c
int			ft_max_int(t_stack *stack);
int			ft_parse(t_stack *stack);
int			ft_error(t_stack *stack);

//util_sorting.c
t_stack		*ft_sort_three(t_stack *stack_a);
t_stacks	ft_sort(t_stacks stacks);
t_stacks	ft_move_up(t_stacks stacks, t_stack *cheapest);
int			ft_get_pos(t_stack *stack_a, int num, int target, int maxint);
t_stacks	ft_set_target(t_stacks stacks);

//util_stack.c
t_stack		*ft_init_stack(int size, char **numbers);
t_stack		*ft_init_a(int size, char **numbers, t_stack *stack_a);
t_stack		*ft_init_a2(char **numbers, t_stack *stack_a);
int			ft_is_sort(t_stack *stack);

//util.c
int			ft_check_follow(char **argv);
int			ft_check_chars(char **argv);
void		ft_set_position(t_stack **stack);
int			ft_get_size(t_stack *stack);
t_stacks	ft_sort_two(t_stacks stacks);

#endif