/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarden <alcarden@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 18:15:37 by alcarden          #+#    #+#             */
/*   Updated: 2023/04/19 20:33:29 by alcarden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned int	i;
	unsigned char	*str;

	i = 0;
	str = s;
	while (n-- > 0)
	{
		str[i] = c;
		i++;
	}
	return (s);
}

// int	main(void)
// {
// 	printf("%d",memset("hola", 4, 4));
// 	printf("%d",ft_memset("hola", 4, 4));
// }
