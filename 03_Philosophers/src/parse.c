/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarden <alcarden@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 18:16:18 by alcarden          #+#    #+#             */
/*   Updated: 2024/07/10 20:02:54 by alcarden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static bool	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || 32 == c)
		return (true);
	return (false);
}

static const char	*ft_valid_args(const char *str)
{
	int			len;
	const char	*num;

	len = 0;
	while (ft_isspace(*str))
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-')
		ft_error_exit("Error: wrong input, only positives numbers\n");
	if (!ft_isdigit(*str))
		ft_error_exit("Error: wrong input, only numbers\n");
	num = str;
	while (ft_isdigit(*str++))
		len++;
	if (len > 10)
		ft_error_exit("Error: wrong input, number too big\n");
	return (num);
}

static long	ft_atol(const char *str)
{
	long	num;

	num = 0;
	str = ft_valid_args(str);
	while (ft_isdigit(*str))
	{
		num = num * 10 + (*str - '0');
		++str;
	}
	if (num > INT_MAX)
		ft_error_exit("Error: wrong input, number too big\n");
	return (num);
}

t_data	*ft_parse_args(t_data *data, int argc, char *argv[])
{
	data = (t_data *)ft_safe_malloc(sizeof(t_data));
	data->nb_full_p = 0;
	data->keep_iterating = true;
	data->nb_philos = ft_atol(argv[1]);
	data->die_time = (u_int64_t)ft_atol(argv[2]);
	data->eat_time = (u_int64_t)ft_atol(argv[3]);
	data->sleep_time = (u_int64_t)ft_atol(argv[4]);
	if (argc == 6)
		data->nb_meals = ft_atol(argv[5]);
	else
		data->nb_meals = -1;
	if (data->nb_philos < 1 || data->nb_philos > 200)
		ft_error_exit("Error: wrong input, number of philos\n");
	if (data->eat_time < 60 || data->sleep_time < 60)
		ft_error_exit("Error: wrong input, time too short\n");
	if (data->nb_meals < 1 && argc == 6)
		ft_error_exit("Error: wrong input, number of meals\n");
	return (data);
}
