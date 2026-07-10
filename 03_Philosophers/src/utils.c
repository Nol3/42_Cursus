/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarden <alcarden@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:29:24 by alcarden          #+#    #+#             */
/*   Updated: 2024/07/11 16:58:53 by alcarden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error_exit(const char *error)
{
	printf("%s\n", error);
	exit(EXIT_FAILURE);
}

void	ft_print_status(t_philo *philo, int index, char s)
{
	pthread_mutex_lock(&philo->data->mut_keep_iter);
	pthread_mutex_lock(&philo->data->mut_print);
	if (philo->data->keep_iterating)
	{
		printf("%lu %i %s\n", ft_start_time() - philo->data->start_time,
			index, ft_select_s(s));
		if (s == 'd')
			philo->data->keep_iterating = false;
	}
	pthread_mutex_unlock(&philo->data->mut_print);
	pthread_mutex_unlock(&philo->data->mut_keep_iter);
}

char	*ft_select_s(char s)
{
	if (s == 'f')
		return ("has taken a fork");
	else if (s == 'e')
		return ("is eating");
	else if (s == 's')
		return ("is sleeping");
	else if (s == 't')
		return ("is thinking");
	else if (s == 'd')
		return ("died");
	return (NULL);
}

void	ft_free_data(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philos)
	{
		pthread_mutex_destroy(&(data->philo[i].mut_state));
		pthread_mutex_destroy(&(data->philo[i].mut_nb_meals_had));
		pthread_mutex_destroy(&(data->philo[i].mut_last_eat_time));
		pthread_mutex_destroy(&data->forks[i]);
	}
	pthread_mutex_destroy(&(data->mut_eat_t));
	pthread_mutex_destroy(&(data->mut_die_t));
	pthread_mutex_destroy(&(data->mut_sleep_t));
	pthread_mutex_destroy(&(data->mut_print));
	pthread_mutex_destroy(&(data->mut_nb_philos));
	pthread_mutex_destroy(&(data->mut_keep_iter));
	pthread_mutex_destroy(&(data->mut_start_time));
	free(data->philo_ths);
	free(data->forks);
	free(data->philo);
	free(data);
}
