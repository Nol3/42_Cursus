/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarden <alcarden@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 18:23:26 by alcarden          #+#    #+#             */
/*   Updated: 2023/04/20 11:28:30 by alcarden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

char	*ft_strnstr(const char	*big, const char *little, size_t len)
{
	size_t	i;
	size_t	x;

	i = 0;
	if (little[i] == '\0')
		return ((char *)big);
	while (big[i] != '\0')
	{
		x = 0;
		while (big[i + x] == little[x] && x + i < len && little[x] != '\0')
		{
			x++;
		}
		if (little[x] == '\0')
		{
			return ((char *)big + i);
		}
		i++;
	}
	return (0);
}
