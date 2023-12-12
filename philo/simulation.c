/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 19:11:38 by agaley            #+#    #+#             */
/*   Updated: 2023/12/12 20:17:39 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	simu_init(t_simu *simu)
{
	simu->is_over = 0;
	simu->nb_forks = 0;
	simu->nb_threads = 0;
	pthread_mutex_init(&simu->log_mtx, NULL);
	pthread_mutex_init(&simu->sync_mtx, NULL);
	forks_init(simu);
	philos_init(simu);
	simu->start_time = ft_time();
	if (simu->args->num_philos == 1)
	{
		usleep(simu->args->time_to_die * 1000);
		log_event(simu->philos[0], E_DIED);
	}
}

void	simu_set_over(t_simu *simu)
{
	pthread_mutex_lock(&simu->sync_mtx);
	simu->is_over = 1;
	pthread_mutex_unlock(&simu->sync_mtx);
}

void	simu_destroy(t_simu *simu, int error)
{
	int	i;

	simu_set_over(simu);
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
	pthread_mutex_destroy(&simu->log_mtx);
	pthread_mutex_destroy(&simu->sync_mtx);
	if (error)
		exit(EXIT_FAILURE);
}

void	*philo_cycle(void *arg)
{
	t_philo	*philo;
	int		is_over;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->simu->sync_mtx);
	is_over = philo->simu->is_over;
	pthread_mutex_unlock(&philo->simu->sync_mtx);
	while (!is_over)
	{
		philo_think(philo);
		pthread_mutex_lock(&philo->simu->sync_mtx);
		is_over = philo->simu->is_over;
		pthread_mutex_unlock(&philo->simu->sync_mtx);
		if (!is_over)
			philo_eat(philo);
		pthread_mutex_lock(&philo->simu->sync_mtx);
		is_over = philo->simu->is_over;
		pthread_mutex_unlock(&philo->simu->sync_mtx);
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
				simu_set_over(simu);
			if (has_eaten_enough(simu->philos[i]))
				simu_set_over(simu);
			i++;
		}
		ft_msleep(simu, 20);
	}
}
