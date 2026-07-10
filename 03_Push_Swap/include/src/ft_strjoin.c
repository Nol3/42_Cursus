/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarden <alcarden@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 17:04:31 by alcarden          #+#    #+#             */
/*   Updated: 2023/04/21 18:21:49 by alcarden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*new;
	unsigned int	size;
	unsigned int	i;
	unsigned int	x;

	size = ft_strlen(s1) + ft_strlen(s2);
	new = (char *)malloc(size * sizeof(char) + 1);
	if (!new)
		return (0);
	i = 0;
	x = 0;
	while (i < size)
	{
		if (i < size - ft_strlen(s2))
			new[i] = s1[i];
		else
		{
			new[i] = s2[x];
			x++;
		}
		i++;
	}
	new[i] = '\0';
	return (new);
}
