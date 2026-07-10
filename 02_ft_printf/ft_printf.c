/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarden <alcarden@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:45:11 by alcarden          #+#    #+#             */
/*   Updated: 2023/05/23 18:19:32 by alcarden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int	ft_check_format(va_list params, char c)
{
	if (c == 'c')
		return (ft_putchar(va_arg(params, int)));
	if (c == 's')
		return (ft_putstr(va_arg(params, char *)));
	if (c == 'p')
		return (ft_putptr(va_arg(params, unsigned long int)));
	if (c == 'd' || c == 'i')
		return (ft_putnbr(va_arg(params, int)));
	if (c == 'u')
		return (ft_putud(va_arg(params, unsigned int)));
	if (c == 'x' || c == 'X')
		return (ft_puthex(c, va_arg(params, unsigned int)));
	if (c == '%')
		return (ft_putchar('%'));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list	list;
	int		i;
	int		chars;

	i = 0;
	chars = 0;
	va_start(list, str);
	while (str[i])
	{
		if (str[i] != '%')
		{
			write(1, &str[i], 1);
			chars++;
		}
		else
		{
			chars = chars + ft_check_format(list, str[i + 1]);
			i++;
		}
		i++;
	}
	va_end(list);
	return (chars);
}
