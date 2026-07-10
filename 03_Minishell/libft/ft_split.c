/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angcampo <angcampo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 20:36:52 by angcampo          #+#    #+#             */
/*   Updated: 2024/02/23 14:26:36 by angcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static void	ft_clear_array(char **strs, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		free(strs[i++]);
	free(strs);
}

static int	ft_pos_char_in_string(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	**ft_initialize_array(const char *s, char c)
{
	char	**res;
	size_t	i;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			i++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	res = malloc(sizeof(char *) * (i + 1));
	if (!res)
		return (NULL);
	return (res);
}

char	**ft_split(const char *s, char c)
{
	char	**res;
	size_t	i;
	size_t	len;

	if (!s)
		return (NULL);
	res = ft_initialize_array(s, c);
	if (!res)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			len = ft_pos_char_in_string(s, c);
			res[i++] = ft_substr(s, 0, len);
			if (!res[i - 1])
				return (ft_clear_array(res, i), NULL);
			s += len;
		}
		else
			++s;
	}
	res[i] = 0;
	return (res);
}
