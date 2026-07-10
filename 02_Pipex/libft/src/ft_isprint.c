/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarden <alcarden@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 18:15:16 by alcarden          #+#    #+#             */
/*   Updated: 2023/04/19 11:48:33 by alcarden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int c)
{
	if (c < 32 || c > 126)
	{
		return (0);
	}
	return (1);
}

// int	main(void)
// {
// 	char	*str;

// 	str = "sdflkjkhasd";
// 	printf("%i", ft_str_is_printable(str));
// 	return (0);
// }