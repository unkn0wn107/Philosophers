/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 19:11:38 by agaley            #+#    #+#             */
/*   Updated: 2023/12/14 02:26:43 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	simu_init(t_simu *simu)
{
	simu->is_over = 0;
	simu->nb_forks = 0;
	simu->nb_thrds_odd = 0;
	simu->nb_thrds_even = 0;
	simu->nb_phi_mtx = 0;
	simu->philos = NULL;
	simu->forks = NULL;
	pthread_mutex_init(&simu->log_mtx, NULL);
	pthread_mutex_init(&simu->sync_mtx, NULL);
	forks_init(simu);
	philos_init(simu);
	simu->start_time = ft_time();
	if (simu->args->num_philos == 1)
	{
		usleep(simu->args->time_to_die * 1000);
		log_event(&simu->philos[0], E_DIED);
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
	while (i < simu->nb_thrds_odd + simu->nb_thrds_even)
		pthread_join(simu->philos[i++].thread, NULL);
	forks_destroy(simu);
	i = 0;
	while (i < simu->nb_phi_mtx)
		pthread_mutex_destroy(&simu->philos[i++].mtx);
	if (simu->philos)
		free(simu->philos);
	pthread_mutex_destroy(&simu->log_mtx);
	pthread_mutex_destroy(&simu->sync_mtx);
	if (error)
		exit(EXIT_FAILURE);
}

int	simu_is_over(t_simu *simu)
{
	int	is_over;

	pthread_mutex_lock(&simu->sync_mtx);
	is_over = simu->is_over;
	pthread_mutex_unlock(&simu->sync_mtx);
	return (is_over);
}

void	simu_run(t_simu *simu)
{
	int	i;

	i = 1;
	while (i < simu->args->num_philos)
	{
		if (pthread_create(&simu->philos[i].thread, NULL,
				philo_cycle, &simu->philos[i]))
			simu_destroy(simu, ERR);
		simu->nb_thrds_odd++;
		i += 2;
	}
	usleep(100);
	i = 0;
	while (i < simu->args->num_philos)
	{
		if (pthread_create(&simu->philos[i].thread, NULL,
				philo_cycle, &simu->philos[i]))
			simu_destroy(simu, ERR);
		simu->nb_thrds_even++;
		i += 2;
	}
	check_philos(simu);
}
