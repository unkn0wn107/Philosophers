/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 19:11:38 by agaley            #+#    #+#             */
/*   Updated: 2023/11/16 02:55:33 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	simu_init(t_simu *simu)
{
	int				i;

	simu->philos = malloc(sizeof(t_philo) * simu->args->num_philos);
	simu->forks = malloc(sizeof(t_fork) * simu->args->num_philos);
	i = 0;
	pthread_mutex_init(simu->log_mutex, NULL);
	while (i < simu->args->num_philos)
	{
		fork_init(simu->forks[i]);
		philo_init(simu, i);
		i++;
	}
}

void	simu_destroy(t_simu *simu)
{
	int	i;

	i = 0;
	while (i < simu->args->num_philos)
	{
		fork_destroy(simu->forks[i]);
		i++;
	}
	pthread_mutex_destroy(simu->log_mutex);
	free(simu->philos);
	free(simu->forks);
}

void	*philo_cycle(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

void	simu_run(t_simu *simu)
{
	int	i;

	i = 0;
	while (i < simu->args->num_philos)
	{
		pthread_create(simu->philos[i]->thread, NULL,
			philo_cycle, simu->philos[i]);
		i++;
	}
	while (!simu->is_over)
	{
		i = 0;
		while (i < simu->args->num_philos)
		{
			if (!is_philo_alive(simu->philos[i]))
			{
				philo_dies(simu->philos[i]);
				simu->is_over = 1;
			}
			if (has_eaten_enough(simu->philos[i]))
				simu->is_over = 1;
			i++;
		}
		ft_usleep(10);
	}
}
