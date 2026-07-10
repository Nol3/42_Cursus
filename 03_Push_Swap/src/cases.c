/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cases.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarden <alcarden@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 00:51:31 by alcarden          #+#    #+#             */
/*   Updated: 2024/03/13 02:45:28 by alcarden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

int	is_case_1(int n, int m, int l)
{
	return (n > m && m < l && n < l);
}

int	is_case_2(int n, int m, int l)
{
	return (n < m && m > l && n > l);
}

int	is_case_3(int n, int m, int l)
{
	return (n > m && m > l);
}

int	is_case_4(int n, int m, int l)
{
	return (n > m && m < l && n > l);
}

int	is_case_5(int n, int m, int l)
{
	return (n < m && m > l && n < l);
}
