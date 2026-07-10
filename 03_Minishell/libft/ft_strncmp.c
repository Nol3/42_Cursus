/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angcampo <angcampo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 20:40:49 by angcampo          #+#    #+#             */
/*   Updated: 2023/09/13 18:50:46 by angcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;	
	int				res;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	res = 0;
	while ((*str1) && (*str2) && (*str1 == *str2) && (n--))
	{
		str1++;
		str2++;
	}
	if ((*str1 != *str2) && (n))
		res = *str1 - *str2;
	return (res);
}
