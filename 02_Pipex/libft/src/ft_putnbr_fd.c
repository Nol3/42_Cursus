/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarden <alcarden@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:36:27 by alcarden          #+#    #+#             */
/*   Updated: 2023/04/24 16:43:59 by alcarden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_nb(int x, int fd)
{
	if (x == 0)
		return ;
	ft_nb(x / 10, fd);
	ft_putchar_fd('0' + x % 10, fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	int	z;

	z = 0;
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write (fd, "-", 1);
		n *= -1;
	}
	if (n <= 9)
	{
		z = (n + '0');
		write(fd, &z, 1);
		return ;
	}
	ft_nb(n, fd);
}
