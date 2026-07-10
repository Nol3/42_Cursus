/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarden <alcarden@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 22:13:01 by alcarden          #+#    #+#             */
/*   Updated: 2024/02/27 21:32:51 by alcarden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long int	ft_atol(const char *c)
{
	long int	num;
	int			cnt;
	int			sign;

	sign = 1;
	num = 0;
	cnt = 0;
	while ((c[cnt] >= 9 && c[cnt] <= 13) || c[cnt] == 32)
		cnt++;
	if (c[cnt] == '-' || c[cnt] == '+')
	{
		if (c[cnt] == '-')
			sign = -1;
		cnt++;
	}
	while ((c[cnt] >= '0' && c[cnt] <= '9') && c[cnt] != '\0')
	{
		num = num * 10 + (c[cnt] - 48);
		cnt++;
	}
	return (num * sign);
}
