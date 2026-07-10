/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarden <alcarden@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 13:18:21 by alcarden          #+#    #+#             */
/*   Updated: 2023/04/19 11:47:46 by alcarden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int c)
{
	if ((c < 65 || c > 90) && (c < 97 || c > 122))
	{
		return (0);
	}
	return (1);
}

// #include <stdio.h>

// int	main (void)
// {
// char	str[] = "ASDF12346";

// 	printf("%i", ft_str_is_alpha(str));
// 	return (0);
// }
