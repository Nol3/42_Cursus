/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angcampo <angcampo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 16:33:14 by angcampo          #+#    #+#             */
/*   Updated: 2023/12/16 10:59:16 by angcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr(char *str)
{
	int	i;
	int	res;

	if (!str)
		return (ft_putstr("(null)"));
	i = 0;
	while (str[i])
	{
		res = ft_putchar(str[i++]);
		if (res < 1)
			return (-1);
	}
	return (i);
}

int	ft_putflag(char c, va_list args)
{
	int	res;

	res = -1;
	if (c == 'c')
		res = ft_putchar(va_arg(args, int));
	else if (c == 's')
		res = ft_putstr(va_arg(args, char *));
	else if (c == 'p')
	{
		if (ft_putstr("0x") == 2)
			res = 2 + ft_print_pointer(va_arg(args, void *));
	}
	else if (c == 'd' || c == 'i')
		res = ft_putnbr_base(va_arg(args, int), "0123456789", 1);
	else if (c == 'u')
		res = ft_putnbr_unsig_base(va_arg(args, int), "0123456789");
	else if (c == 'x')
		res = ft_putnbr_unsig_base(va_arg(args, int), "0123456789abcdef");
	else if (c == 'X')
		res = ft_putnbr_unsig_base(va_arg(args, int), "0123456789ABCDEF");
	else if (c == '%')
		res = ft_putchar('%');
	if (res < 0)
		return (INT_MIN);
	return (res);
}

int	ft_printf(char const *str, ...)
{
	va_list	args;
	int		count;

	if (!str)
		return (-1);
	va_start(args, str);
	count = 0;
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			count += ft_putflag(*str, args);
		}
		else
			count += ft_putchar(*str);
		if (count < 0)
			return (-1);
		str++;
	}
	return (count);
}
