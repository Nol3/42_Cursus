/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angcampo <angcampo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 16:18:19 by angcampo          #+#    #+#             */
/*   Updated: 2024/07/07 19:59:32 by angcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset_gnl(void *b, int c, size_t len)
{
	unsigned char	*str;

	str = (unsigned char *) b;
	while (len--)
	{
		*str = (unsigned char) c;
		str++;
	}
	return (b);
}

int	ft_pos_char_in_string_gnl(const char *s, char c)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static size_t	ft_strlcpy_gnl(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (*src && i + 1 < dstsize)
	{
		*dst++ = *src++;
		++i;
	}
	if (dstsize)
		*dst = '\0';
	while (*src++)
		++i;
	return (i);
}

char	*ft_strjoin_gnl(char *s1, char const *s2)
{
	char	*dst;
	int		s1_len;
	int		s2_len;

	s2_len = ft_pos_char_in_string_gnl(s2, '\0');
	if (!s1)
	{
		dst = ft_substr_gnl(s2, 0, s2_len);
		return (dst);
	}
	s1_len = ft_pos_char_in_string_gnl(s1, '\0');
	dst = (char *)malloc(s1_len
			+ s2_len + 1);
	if (!dst)
		return (NULL);
	ft_strlcpy_gnl(dst, s1, s1_len + 1);
	ft_strlcpy_gnl(dst + s1_len, s2,
		s2_len + 1);
	if (s1)
		free(s1);
	return (dst);
}

char	*ft_substr_gnl(char const *s, unsigned int start, size_t len)
{
	char	*dst;

	if (start >= (unsigned int)ft_pos_char_in_string_gnl(s, '\0'))
		len = 0;
	else if (len > (size_t)ft_pos_char_in_string_gnl(s + start, '\0'))
		len = (size_t)ft_pos_char_in_string_gnl(s + start, '\0');
	dst = (char *)malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (NULL);
	if (start < (unsigned int)ft_pos_char_in_string_gnl(s, '\0'))
		ft_strlcpy_gnl(dst, s + start, len + 1);
	else
		ft_strlcpy_gnl(dst, "", 1);
	if (!ft_pos_char_in_string_gnl(dst, '\0'))
	{
		free(dst);
		return (NULL);
	}
	return (dst);
}
