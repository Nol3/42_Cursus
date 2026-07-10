/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angcampo <angcampo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 19:47:22 by angcampo          #+#    #+#             */
/*   Updated: 2023/09/12 20:00:43 by angcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Creates a buffer
Copies first string
Moves dst and copies second string
*/
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;

	dst = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (dst == 0)
		return (0);
	ft_strlcpy(dst, s1, ft_strlen(s1) + 1);
	ft_strlcpy(dst + ft_strlen(s1), s2, ft_strlen(s2) + 1);
	return (dst);
}
