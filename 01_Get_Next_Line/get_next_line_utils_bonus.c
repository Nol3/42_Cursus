/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarden <alcarden@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:11:19 by alcarden          #+#    #+#             */
/*   Updated: 2023/05/25 21:25:10 by alcarden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	cnt;

	cnt = 0;
	if (!str)
		return (0);
	while (str[cnt] != '\0')
		cnt++;
	return (cnt);
}

char	*ft_strjoin(char *buff, char *stack)
{
	char	*res;
	int		cnt;
	int		cnt2;

	if (!stack)
	{
		stack = malloc(1);
		stack[0] = '\0';
	}
	if (!stack || !buff)
		return (0);
	res = malloc(sizeof(char) * (ft_strlen(buff) + ft_strlen(stack)) + 1);
	if (!res)
		return (0);
	cnt = -1;
	cnt2 = 0;
	if (stack)
		while (stack[++cnt] != '\0')
			res[cnt] = stack[cnt];
	while (buff[cnt2] != '\0')
		res[cnt++] = buff[cnt2++];
	res[cnt] = '\0';
	free(stack);
	return (res);
}

char	*ft_strchr(char *str, char c)
{
	int	cnt;

	cnt = 0;
	if (!str)
		return (0);
	while (str[cnt] != '\0')
	{
		if (str[cnt] == c)
			return (&str[cnt]);
		cnt++;
	}
	return (0);
}
