/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 19:11:38 by agaley            #+#    #+#             */
/*   Updated: 2023/11/30 01:10:34 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	simu_init(t_simu *simu)
{
	pthread_mutex_init(&simu->log_mutex, NULL);
	forks_init(simu);
	philos_init(simu);
}

void	forks_init(t_simu *simu)
{
	int	i;

	simu->forks = malloc(sizeof(t_fork *) * simu->args->num_philos);
	if (!simu->forks)
		simu_destroy(simu, 1);
	i = 0;
	while (i < simu->args->num_philos)
	{
		simu->forks[i] = malloc(sizeof(t_fork));
		if (!simu->forks[i])
			simu_destroy(simu, 1);
		if (!fork_init(simu->forks[i++]))
			simu_destroy(simu, 1);
	}
}

void	philos_init(t_simu *simu)
{
	int	i;

	simu->philos = malloc(sizeof(t_philo *) * simu->args->num_philos);
	if (!simu->philos)
		simu_destroy(simu, 1);
	i = 0;
	while (i < simu->args->num_philos)
	{
		simu->philos[i] = malloc(sizeof(t_philo));
		if (!simu->philos[i])
			simu_destroy(simu, 1);
		philo_init(simu, i++);
	}
}

void	simu_destroy(t_simu *simu, int error)
{
	int	i;

	i = 0;
	while (simu->forks && simu->forks[i])
		fork_destroy(simu->forks[i]);
	if (simu->forks)
		free(simu->forks);
	while (simu->philos && simu->philos[i])
		free(simu->philos[i]);
	if (simu->philos)
		free(simu->philos);
	pthread_mutex_destroy(&simu->log_mutex);
	free(simu);
	if (error)
		exit(EXIT_FAILURE);
}

void	*philo_cycle(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo->dead)
	{
		philo_eat(philo);
		if (philo->simu->is_over)
		{
			pthread_exit(NULL);
			return (NULL);
		}
		philo_sleep(philo);
		if (philo->simu->is_over)
		{
			pthread_exit(NULL);
			return (NULL);
		}
		philo_think(philo);
		if (philo->simu->is_over)
		{
			pthread_exit(NULL);
			return (NULL);
		}
	}
	philo_dies(philo);
	pthread_exit(NULL);
	return (NULL);
}

void	simu_over_set_philos(t_simu *simu, int philo_id, int dead)
{
	if (dead)
		philo_dies(simu->philos[philo_id]);
	simu->is_over = 1;
}

void	simu_run(t_simu *simu)
{
	int		i;

	i = 0;
	while (i < simu->args->num_philos)
	{
		printf("%p\n", simu);
		if (pthread_create(&simu->philos[i]->thread, NULL,
				philo_cycle, simu->philos[i]))
			exit(EXIT_FAILURE);
		i++;
	}
	while (!simu->is_over)
	{
		i = 0;
		while (!simu->is_over && i < simu->args->num_philos)
		{
			if (!is_philo_alive(simu->philos[i]))
				simu->is_over = 1;
			if (has_eaten_enough(simu->philos[i]))
				simu->is_over = 1;
			i++;
		}
		ft_usleep(10);
	}
	i = 0;
	while (i < simu->args->num_philos)
		pthread_join(simu->philos[i++]->thread, NULL);
}
