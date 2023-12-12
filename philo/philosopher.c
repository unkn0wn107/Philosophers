/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 19:11:52 by agaley            #+#    #+#             */
/*   Updated: 2023/12/12 23:15:48 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	philos_init(t_simu *simu)
{
	simu->philos = malloc(sizeof(t_philo) * simu->args->num_philos);
	if (!simu->philos)
		simu_destroy(simu, 1);
	simu->nb_philos = 0;
	while (simu->nb_philos < simu->args->num_philos)
	{
		simu->philos[simu->nb_philos] = malloc(sizeof(t_philo));
		if (!simu->philos[simu->nb_philos])
			simu_destroy(simu, 1);
		philo_init(simu, simu->nb_philos++);
	}
}

void	philo_init(t_simu *simu, int i)
{
	simu->philos[i]->id = i + 1;
	simu->philos[i]->num_eats = -1;
	simu->philos[i]->last_meal_time = ft_time();
	simu->philos[i]->dead = 0;
	simu->philos[i]->simu = simu;
	simu->philos[i]->l_fork = simu->forks[i];
	simu->philos[i]->r_fork = simu->forks[(i + 1) % simu->args->num_philos];
}

void	philo_eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		fork_pick(philo->l_fork);
		log_event(philo, E_PICK_FORK);
		fork_pick(philo->r_fork);
		log_event(philo, E_PICK_FORK);
	}
	else
	{
		fork_pick(philo->r_fork);
		log_event(philo, E_PICK_FORK);
		fork_pick(philo->l_fork);
		log_event(philo, E_PICK_FORK);
	}
	pthread_mutex_lock(&philo->simu->sync_mtx);
	philo->last_meal_time = ft_time();
	philo->num_eats++;
	pthread_mutex_unlock(&philo->simu->sync_mtx);
	log_event(philo, E_EAT);
	ft_msleep(philo->simu, philo->simu->args->time_to_eat);
	fork_drop(philo->l_fork);
	fork_drop(philo->r_fork);
}

void	philo_sleep(t_philo *philo)
{
	log_event(philo, E_SLEEP);
	ft_msleep(philo->simu, philo->simu->args->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	log_event(philo, E_THINK);
}
