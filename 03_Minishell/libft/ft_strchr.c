/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angcampo <angcampo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 20:18:27 by angcampo          #+#    #+#             */
/*   Updated: 2023/09/13 17:46:09 by angcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
If we find c, we return first occurence
If not, we return NULL
*/
char	*ft_strchr(const char *s, int c)
{
	while (*s != (char) c)
		if (!*s++)
			return (0);
	return ((char *)s);
}
