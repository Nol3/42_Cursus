/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarden <alcarden@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 18:16:45 by alcarden          #+#    #+#             */
/*   Updated: 2023/04/19 12:30:40 by alcarden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
	{
		c += 32;
	}
	return (c);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char str[] = "ALEXZ";

// 	printf("%s", ft_strlowcase(str));
// 	return (0);
// }
