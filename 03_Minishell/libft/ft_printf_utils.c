/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angcampo <angcampo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 18:03:46 by angcampo          #+#    #+#             */
/*   Updated: 2023/12/16 11:01:17 by angcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar(char c)
{
	int	res;

	res = write(1, &c, 1);
	if (res < 0)
		return (-1);
	return (res);
}

int	ft_putnbr_unsig_base(unsigned int nbr, const char *base)
{
	unsigned int	size_base;
	int				res;
	int				res2;

	size_base = (unsigned int) ft_strlen(base);
	if (nbr < size_base)
	{
		res = ft_putchar(base[nbr]);
		if (res == -1)
			return (-1);
		return (res);
	}
	else
	{
		res = ft_putnbr_unsig_base(nbr / size_base, base);
		if (res == -1)
			return (-1);
		res2 = ft_putchar(base[nbr % size_base]);
		if (res2 == -1)
			return (-1);
		return (res + res2);
	}
}

int	ft_putnbr_base(int nbr, const char *base, int sign)
{
	unsigned int	nb;
	int				res;
	int				res2;

	res = 0;
	if (nbr < 0)
	{
		nb = 4294967295 - (unsigned int) nbr + 1;
		if (sign)
			res = ft_putchar('-');
		if (res == -1)
			return (-1);
		res2 = ft_putnbr_unsig_base(nb, base);
		if (res2 == -1)
			return (-1);
		return (res + res2);
	}
	else
	{
		nb = (unsigned int) nbr;
		res = ft_putnbr_unsig_base(nb, base);
		if (res < 0)
			return (-1);
		return (res);
	}
}

int	ft_print_pointer(void *pointer)
{
	const char	*base = "0123456789abcdef";
	size_t		nbr;
	size_t		size_base;
	int			res;
	int			res2;

	nbr = (size_t) pointer;
	size_base = (size_t) ft_strlen(base);
	if (nbr < size_base)
	{
		res = ft_putchar(base[nbr]);
		if (res == -1)
			return (-1);
		return (res);
	}
	else
	{
		res = ft_print_pointer((void *)(nbr / size_base));
		if (res == -1)
			return (-1);
		res2 = ft_putchar(base[nbr % size_base]);
		if (res2 == -1)
			return (-1);
		return (res + res2);
	}
}
