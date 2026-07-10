/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angcampo <angcampo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 19:18:38 by angcampo          #+#    #+#             */
/*   Updated: 2023/09/13 19:31:03 by angcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dst;

	if (start >= (unsigned int)ft_strlen(s))
		len = 0;
	else if (len > (size_t) ft_strlen(s + start))
		len = (size_t) ft_strlen(s + start);
	dst = (char *)malloc(sizeof(char) * (len + 1));
	if (dst == 0)
		return (0);
	if (start < (unsigned int)ft_strlen(s))
		ft_strlcpy(dst, s + start, len + 1);
	else
		ft_strlcpy(dst, "", 1);
	return (dst);
}
