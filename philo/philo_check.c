/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 02:19:10 by agaley            #+#    #+#             */
/*   Updated: 2023/12/13 19:38:20 by agaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*check_philos(void *arg)
{
	int		i;
	t_simu	*simu;

	simu = (t_simu *)arg;
	while (!simu->is_over)
	{
		usleep(4000);
		i = 0;
		pthread_mutex_lock(&simu->sync_mtx);
		while (!simu->is_over && i < simu->args->num_philos)
		{
			if (ft_time() - simu->philos[i]->last_meal_time
				> simu->philos[i]->simu->args->time_to_die)
			{
				simu->philos[i]->dead = 1;
				simu->is_over = 1;
			}
			if (simu->args->min_eats != -1
				&& simu->args->min_eats < simu->philos[i]->num_eats)
				simu->is_over = 1;
			i++;
		}
		pthread_mutex_unlock(&simu->sync_mtx);
	}
	return (NULL);
}

int	philo_is_dead(t_philo *philo)
{
	int	is_dead;

	pthread_mutex_lock(&philo->simu->sync_mtx);
	is_dead = philo->dead;
	pthread_mutex_unlock(&philo->simu->sync_mtx);
	return (is_dead);
}
