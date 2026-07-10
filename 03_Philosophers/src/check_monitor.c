/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarden <alcarden@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:42:21 by alcarden          #+#    #+#             */
/*   Updated: 2024/07/11 16:25:05 by alcarden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_full(t_data *data)
{
	int	i;
	int	full;

	i = 0;
	full = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_lock(&(data->philo[i].mut_nb_meals_had));
		if (data->philo[i].nb_meals_had >= data->nb_meals
			&& data->nb_meals != -1)
		{
			pthread_mutex_unlock(&(data->philo[i].mut_nb_meals_had));
			full++;
			if (full == data->nb_philos)
				return (1);
		}
		pthread_mutex_unlock(&(data->philo[i].mut_nb_meals_had));
		i++;
	}
	return (0);
}

int	ft_check_alive(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philos)
	{
		pthread_mutex_lock(&(data->philo[i].mut_last_eat_time));
		if (ft_start_time() - data->philo[i].last_eat_time > data->die_time)
		{
			ft_print_status(&data->philo[i], data->philo[i].id, 'd');
			ft_set_philo_state(&data->philo[i], DEAD);
			ft_set_keep_iter(data, false);
			pthread_mutex_unlock(&(data->philo[i].mut_last_eat_time));
			return (1);
		}
		pthread_mutex_unlock(&(data->philo[i].mut_last_eat_time));
	}
	return (0);
}
