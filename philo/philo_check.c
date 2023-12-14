/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 02:19:10 by agaley            #+#    #+#             */
/*   Updated: 2023/12/14 02:59:37 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	check_philos(t_simu	*simu)
{
	int		i;

	while (!simu->is_over)
	{
		usleep(3000);
		i = 0;
		while (!simu->is_over && i < simu->args->num_philos)
		{
			pthread_mutex_lock(&simu->philos[i].mtx);
			if (ft_time() - simu->philos[i].last_meal_time
				> simu->args->time_to_die)
			{
				simu->philos[i].dead = 1;
				simu_set_over(simu);
			}
			if (simu->args->min_eats != -1
				&& simu->args->min_eats < simu->philos[i].num_eats)
				simu_set_over(simu);
			pthread_mutex_unlock(&simu->philos[i++].mtx);
		}
	}
}

int	philo_is_dead(t_philo *philo)
{
	int	is_dead;

	pthread_mutex_lock(&philo->mtx);
	is_dead = philo->dead;
	pthread_mutex_unlock(&philo->mtx);
	return (is_dead);
}
