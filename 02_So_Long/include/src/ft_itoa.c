/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarden <alcarden@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:46:03 by alcarden          #+#    #+#             */
/*   Updated: 2023/04/27 18:21:36 by alcarden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_digits(int nbr)
{
	int	digit;

	digit = 0;
	if (nbr == 0)
		return (1);
	if (nbr < 0)
	{
		nbr *= -1;
		digit++;
	}
	while (nbr > 0)
	{
		digit++;
		nbr /= 10;
	}
	return (digit);
}

char	*ft_negative(char *dest, char *src)
{
	int	i;

	dest = malloc(12 * sizeof(char));
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (i < 11)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		d;
	int		nb;

	str = NULL;
	if (n == -2147483648)
		return (ft_negative(str, "-2147483648"));
	nb = n;
	d = ft_digits(nb);
	if (n < 0)
		nb *= -1;
	str = malloc((d + 1) * sizeof(char));
	if (str == NULL)
		return (0);
	str[d] = '\0';
	while (d > 0)
	{
		str[d - 1] = (nb % 10) + 48;
		nb /= 10;
		d--;
	}
	if (n < 0)
		str[d] = '-';
	return (str);
}
