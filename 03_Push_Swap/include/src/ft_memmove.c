/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarden <alcarden@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 16:11:15 by alcarden          #+#    #+#             */
/*   Updated: 2023/04/27 18:40:19 by alcarden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*tmp;
	char	*d;
	size_t	i;

	i = 0;
	tmp = (char *)src;
	d = (char *)dest;
	if (!dest && !src)
		return (dest);
	if (tmp < d)
	{
		while (n--)
			d[n] = tmp[n];
	}
	else
	{
		while (i < n)
		{
			d[i] = tmp[i];
			i++;
		}
	}
	return (d);
}
