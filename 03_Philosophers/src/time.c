/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarden <alcarden@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:35:47 by alcarden          #+#    #+#             */
/*   Updated: 2024/07/11 16:18:30 by alcarden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_start_time(void)
{
	struct timeval	time;
	long			start_time;

	gettimeofday(&time, NULL);
	start_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (start_time);
}

int	ft_usleep(long time)
{
	long	start_time;

	start_time = ft_start_time();
	while (ft_start_time() - start_time < time)
		usleep(1);
	return (0);
}

long	ft_current_time(long start_time)
{
	struct timeval	time;
	long			current_time;

	gettimeofday(&time, NULL);
	current_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (current_time - start_time);
}
