/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angcampo <angcampo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 20:08:16 by angcampo          #+#    #+#             */
/*   Updated: 2023/09/14 20:22:30 by angcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_char_in_string(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != c)
		i++;
	return (str[i] == c);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*result;
	unsigned int	start;
	unsigned int	end;
	unsigned int	size;

	start = 0;
	end = 0;
	size = 1;
	if (ft_strlen(s1))
		end = ft_strlen(s1) - 1;
	while (s1[start] && ft_char_in_string(set, s1[start]))
		start++;
	while (end && ft_char_in_string(set, s1[end]))
		end--;
	if (start <= end)
		size = end - start + 2;
	if (!start && !end)
		size = 1;
	result = (char *)malloc(sizeof(char) * size);
	if (result == 0)
		return (0);
	ft_strlcpy(result, s1 + start, size);
	return (result);
}
