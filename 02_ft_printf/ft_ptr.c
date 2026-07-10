/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarden <alcarden@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:56:53 by alcarden          #+#    #+#             */
/*   Updated: 2023/05/23 18:20:15 by alcarden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puthexp(long unsigned int ptr, int num)
{
	char	*base;

	base = "0123456789abcdef";
	if (num > 0)
	{
		if (ptr > 15)
			ft_puthexp(ptr / 16, num - 1);
		write(1, &base[ptr % 16], 1);
	}
	return (ft_count_hex(ptr));
}

int	ft_putptr(long unsigned int ptr)
{
	int	num;

	if (ptr == 0)
	{
		write(1, "0x0", 3);
		return (3);
	}
	write(1, "0x", 2);
	num = ft_puthexp(ptr, 16);
	return (num + 2);
}
