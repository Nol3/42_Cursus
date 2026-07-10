/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gets.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarden <alcarden@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:23:26 by alcarden          #+#    #+#             */
/*   Updated: 2024/07/11 17:02:50 by alcarden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_get_philo_state(t_philo *philo)
{
	int	state;

	pthread_mutex_lock(&(philo->mut_state));
	state = philo->state;
	pthread_mutex_unlock(&(philo->mut_state));
	return (state);
}

bool	ft_get_keep_iter(t_data *data)
{
	bool	keep_iter;

	pthread_mutex_lock(&(data->mut_keep_iter));
	keep_iter = data->keep_iterating;
	pthread_mutex_unlock(&(data->mut_keep_iter));
	return (keep_iter);
}
