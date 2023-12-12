/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 02:19:10 by agaley            #+#    #+#             */
/*   Updated: 2023/12/12 19:22:50 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	has_eaten_enough(t_philo *philo)
{
	pthread_mutex_lock(&philo->simu->sync_mtx);
	if (philo->simu->args->min_eats == 0
		|| philo->simu->args->min_eats < philo->num_eats)
	{
		pthread_mutex_unlock(&philo->simu->sync_mtx);
		return (0);
	}
	pthread_mutex_unlock(&philo->simu->sync_mtx);
	return (1);
}

int	is_philo_alive(t_philo *philo)
{
	pthread_mutex_lock(&philo->simu->sync_mtx);
	if (ft_time() - philo->last_meal_time > philo->simu->args->time_to_die)
	{
		philo->dead = 1;
		pthread_mutex_unlock(&philo->simu->sync_mtx);
		return (0);
	}
	pthread_mutex_unlock(&philo->simu->sync_mtx);
	return (1);
}
