/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarden <alcarden@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 18:13:09 by alcarden          #+#    #+#             */
/*   Updated: 2023/04/20 11:45:21 by alcarden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

size_t	ft_strlcat(char *dest, char *src, unsigned int size)
{
	unsigned int	i;
	unsigned int	x;
	unsigned int	y;
	unsigned int	z;

	i = 0;
	x = 0;
	while (dest[x] != '\0')
	{
		x++;
	}
	y = ft_strlen((char *)dest);
	z = ft_strlen((char *)src);
	if (size <= y)
		return (z + size);
	while (src[i] != '\0' && i < (size - y - 1))
	{
		dest[x] = src[i];
		x++;
		i++;
	}
	dest[x] = '\0';
	return (y + z);
}

// #include <stdio.h>
// #include <string.h>

// int main(void)
// {
// 	char	dest[123] = "Cardenas";
// 	char	dest_2[123] = "Cardenas";

// 	char	src[123] = "Alejandro ";
// 	char	src_2[123] = "Alejandro ";
// 	unsigned int i = 4;

// 	printf("%d%s\n", ft_strlcat(dest, src, i), dest);
// 	printf("%lu%s", strlcat(dest_2, src_2, i), dest_2);
// }
