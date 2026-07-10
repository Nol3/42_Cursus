/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarden <alcarden@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 18:16:48 by alcarden          #+#    #+#             */
/*   Updated: 2023/04/19 12:30:25 by alcarden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
	{
		c -= 32;
	}
	return (c);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char str[] = "alejandroz";

// 	printf("%s", ft_strupcase(str));
// 	return (0);
// }
