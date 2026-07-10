/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarden <alcarden@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 17:34:49 by alcarden          #+#    #+#             */
/*   Updated: 2023/04/20 13:08:27 by alcarden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdint.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*x;
	unsigned char	*y;

	i = 0;
	x = (unsigned char *)s1;
	y = (unsigned char *)s2;
	if (!x && !y)
		return (0);
	while (i < n)
	{
		if (x[i] > y[i])
		{
			return (x[i] - y[i]);
		}
		if (x[i] < y[i])
		{
			return (x[i] - y[i]);
		}
		i++;
	}
	return (0);
}
