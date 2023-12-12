/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 19:11:38 by agaley            #+#    #+#             */
/*   Updated: 2023/12/12 13:24:43 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	simu_init(t_simu *simu)
{
	simu->is_over = 0;
	simu->nb_forks = 0;
	simu->nb_threads = 0;
	pthread_mutex_init(&simu->log_mutex, NULL);
	forks_init(simu);
	philos_init(simu);
	simu->start_time = ft_time();
}

void	forks_init(t_simu *simu)
{
	simu->forks = malloc(sizeof(t_fork *) * simu->args->num_philos);
	if (!simu->forks)
		simu_destroy(simu, 1);
	while (simu->nb_forks < simu->args->num_philos)
	{
		simu->forks[simu->nb_forks] = malloc(sizeof(t_fork));
		if (!simu->forks[simu->nb_forks])
			simu_destroy(simu, 1);
		if (!fork_init(simu->forks[simu->nb_forks++]))
			simu_destroy(simu, 1);
	}
}

void	philos_init(t_simu *simu)
{
	int	i;

	simu->philos = malloc(sizeof(t_philo) * simu->args->num_philos);
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

	pthread_mutex_lock(&simu->log_mutex);
	simu->is_over = 1;
	pthread_mutex_unlock(&simu->log_mutex);
	i = 0;
	while (i < simu->nb_threads)
		pthread_join(simu->philos[i++]->thread, NULL);
	i = 0;
	while (simu->forks && i < simu->nb_forks)
		fork_destroy(simu->forks[i++]);
	if (simu->forks)
		free(simu->forks);
	i = 0;
	while (i < simu->nb_threads)
		free(simu->philos[i++]);
	if (simu->philos)
		free(simu->philos);
	pthread_mutex_destroy(&simu->log_mutex);
	if (error)
		exit(EXIT_FAILURE);
}

void	*philo_cycle(void *arg)
{
	t_philo	*philo;
	int		is_over;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->simu->log_mutex);
	is_over = philo->simu->is_over;
	pthread_mutex_unlock(&philo->simu->log_mutex);
	while (!is_over)
	{
		philo_think(philo);
		pthread_mutex_lock(&philo->simu->log_mutex);
		is_over = philo->simu->is_over;
		pthread_mutex_unlock(&philo->simu->log_mutex);
		if (!is_over)
			philo_eat(philo);
		pthread_mutex_lock(&philo->simu->log_mutex);
		is_over = philo->simu->is_over;
		pthread_mutex_unlock(&philo->simu->log_mutex);
		if (!is_over)
			philo_sleep(philo);
	}
	if (philo->dead)
		log_event(philo, E_DIED);
	pthread_exit(NULL);
	return (NULL);
}

void	simu_run(t_simu *simu)
{
	int	i;

	while (simu->nb_threads < simu->args->num_philos)
	{
		if (pthread_create(&simu->philos[simu->nb_threads]->thread, NULL,
				philo_cycle, simu->philos[simu->nb_threads]))
			simu_destroy(simu, 1);
		simu->nb_threads++;
	}
	while (!simu->is_over)
	{
		i = 0;
		while (!simu->is_over && i < simu->args->num_philos)
		{
			if (!is_philo_alive(simu->philos[i]))
			{
				pthread_mutex_lock(&simu->log_mutex);
				simu->is_over = 1;
				pthread_mutex_unlock(&simu->log_mutex);
			}
			if (has_eaten_enough(simu->philos[i]))
			{
				pthread_mutex_lock(&simu->log_mutex);
				simu->is_over = 1;
				pthread_mutex_unlock(&simu->log_mutex);
			}			i++;
		}
		ft_usleep(simu, 5);
	}
}
