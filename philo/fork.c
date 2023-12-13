/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 22:43:24 by agaley            #+#    #+#             */
/*   Updated: 2023/12/12 19:29:26 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	forks_init(t_simu *simu)
{
	simu->forks = malloc(sizeof(t_fork) * simu->args->num_philos);
	if (!simu->forks)
		simu_destroy(simu, 1);
	while (simu->nb_forks < simu->args->num_philos)
		if (pthread_mutex_init(&simu->forks[simu->nb_forks++], NULL))
			simu_destroy(simu, 1);
}

void	forks_destroy(t_simu *simu)
{
	while (simu->nb_forks--)
		pthread_mutex_destroy(&simu->forks[simu->nb_forks]);
	free(simu->forks);
}

void	fork_pick(t_fork *fork)
{
	pthread_mutex_lock(fork);
}

void	fork_drop(t_fork *fork)
{
	pthread_mutex_unlock(fork);
}
