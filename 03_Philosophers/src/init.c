/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarden <alcarden@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:54:59 by alcarden          #+#    #+#             */
/*   Updated: 2024/07/11 16:39:23 by alcarden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	ft_init_philo(int id, t_data *data)
{
	t_philo	philo;

	philo.id = id;
	philo.nb_meals_had = 0;
	philo.is_alive = 1;
	philo.data = data;
	philo.state = IDLE;
	philo.left_f = &(data->forks[id]);
	philo.right_f = &(data->forks[(id + 1) % data->nb_philos]);
	ft_safe_mutex_handle(&(philo.mut_state), INIT);
	ft_safe_mutex_handle(&(philo.mut_nb_meals_had), INIT);
	ft_safe_mutex_handle(&(philo.mut_last_eat_time), INIT);
	ft_update_last_meal_time(&philo);
	return (philo);
}

t_data	*ft_init_data(int nb_philos, t_data *data)
{
	int		i;

	i = -1;
	data->nb_full_p = 0;
	data->start_time = 0;
	ft_safe_mutex_handle(&(data->mut_eat_t), INIT);
	ft_safe_mutex_handle(&(data->mut_die_t), INIT);
	ft_safe_mutex_handle(&(data->mut_sleep_t), INIT);
	ft_safe_mutex_handle(&(data->mut_print), INIT);
	ft_safe_mutex_handle(&(data->mut_nb_philos), INIT);
	ft_safe_mutex_handle(&(data->mut_keep_iter), INIT);
	ft_safe_mutex_handle(&(data->mut_start_time), INIT);
	data->philo_ths = ft_safe_malloc(nb_philos * sizeof(pthread_t));
	data->forks = ft_safe_malloc(nb_philos * sizeof(pthread_mutex_t));
	data->philo = ft_safe_malloc(nb_philos * sizeof(t_philo));
	while (++i < data->nb_philos)
	{
		ft_safe_mutex_handle(&(data->forks[i]), INIT);
		data->philo[i] = ft_init_philo(i, data);
	}
	return (data);
}

void	ft_load_last_meal_time(t_philo *philo)

{
	ft_safe_mutex_handle(&(philo->mut_last_eat_time), LOCK);
	philo->last_eat_time = ft_current_time(philo->data->start_time);
	ft_safe_mutex_handle(&(philo->mut_last_eat_time), UNLOCK);
}
