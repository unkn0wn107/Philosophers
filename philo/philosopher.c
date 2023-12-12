/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 19:11:52 by agaley            #+#    #+#             */
/*   Updated: 2023/12/11 18:27:51 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	philo_init(t_simu *simu, int i)
{
	simu->philos[i]->id = i + 1;
	simu->philos[i]->num_eats = 0;
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
	philo->last_meal_time = ft_time();
	philo->num_eats++;
	log_event(philo, E_EAT);
	ft_usleep(philo->simu, philo->simu->args->time_to_eat); // Boucle sleep pour arreter la simulation
	fork_drop(philo->l_fork);
	fork_drop(philo->r_fork);
}

void	philo_sleep(t_philo *philo)
{
	log_event(philo, E_SLEEP);
	ft_usleep(philo->simu, philo->simu->args->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	log_event(philo, E_THINK);
}

