/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarden <alcarden@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 18:15:12 by alcarden          #+#    #+#             */
/*   Updated: 2023/04/19 11:43:55 by alcarden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	while (c >= 48 && c <= 57)
	{
		return (1);
	}
	return (0);
}

// #include <stdio.h>
// int main(void)
// {
// 	unsigned char x[] = "2135465";
// 	printf("%i", ft_isdigit(x));
// }