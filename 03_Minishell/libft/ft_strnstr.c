/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angcampo <angcampo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 18:44:41 by angcampo          #+#    #+#             */
/*   Updated: 2023/09/13 18:35:37 by angcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	size;
	char	*res;

	size = (size_t) ft_strlen(needle);
	res = 0;
	if (!ft_strncmp(haystack, needle, size) && len >= size)
		res = (char *)haystack;
	if (*haystack)
		haystack++;
	while ((len-- > size) && (*haystack) && (!res))
	{
		if (!ft_strncmp(haystack, needle, size))
			res = (char *)haystack;
		haystack++;
	}
	return (res);
}
