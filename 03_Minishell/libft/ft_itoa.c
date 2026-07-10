/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angcampo <angcampo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:22:39 by angcampo          #+#    #+#             */
/*   Updated: 2023/09/14 19:30:00 by angcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_number_size(int n)
{
	if (n == -2147483648)
		return (11);
	else if (n < 0)
		return (1 + get_number_size(-n));
	else if (n < 10)
		return (1);
	else
		return (1 + get_number_size(n / 10));
}

static void	ft_add_char_to_string(char *str, char c)
{
	while (*str)
		str++;
	*str = c;
	str++;
	*str = '\0';
}

static int	ft_recursive_power(int nb, int power)
{
	int	res;

	if (power < 0)
		res = 0;
	else if (power == 0)
		res = 1;
	else
		res = nb * ft_recursive_power(nb, power - 1);
	return (res);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		exp;

	result = (char *)malloc(sizeof(char) * (get_number_size(n) + 1));
	if (!result)
		return (NULL);
	ft_bzero(result, get_number_size(n) + 1);
	if (n == -2147483648)
	{
		ft_strlcpy(result, "-2147483648", get_number_size(n) + 1);
		return (result);
	}
	if (n < 0)
	{
		ft_add_char_to_string(result, '-');
		n = 0 - n;
	}
	exp = ft_recursive_power(10, get_number_size(n) - 1);
	while (exp)
	{
		ft_add_char_to_string(result, '0' + (n / exp) % 10);
		exp /= 10;
	}
	return (result);
}

/*
int	main(void)
{
	printf("%s\n", ft_itoa(-1031720409));
}
*/