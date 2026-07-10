/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sets.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarden <alcarden@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:23:20 by alcarden          #+#    #+#             */
/*   Updated: 2024/07/11 16:18:26 by alcarden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_set_keep_iter(t_data *data, bool value)
{
	pthread_mutex_lock(&(data->mut_keep_iter));
	data->keep_iterating = value;
	pthread_mutex_unlock(&(data->mut_keep_iter));
}

void	ft_set_philo_state(t_philo *philo, t_state state)
{
	pthread_mutex_lock(&(philo->mut_state));
	philo->state = state;
	pthread_mutex_unlock(&(philo->mut_state));
}
