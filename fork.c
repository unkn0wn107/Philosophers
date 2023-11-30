/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 22:43:24 by agaley            #+#    #+#             */
/*   Updated: 2023/11/19 23:57:46 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	fork_init(t_fork *fork)
{
	fork->mutex = malloc(sizeof(pthread_mutex_t));
	if (!fork->mutex)
	{
		free(fork);
		return (0);
	}
	if (pthread_mutex_init(fork->mutex, NULL))
	{
		free(fork->mutex);
		free(fork);
		return (0);
	}
	return (1);
}

void	fork_destroy(t_fork *fork)
{
	if (fork->mutex)
	{
		pthread_mutex_destroy(fork->mutex);
		free(fork->mutex);
	}
	free(fork);
}

void	fork_pick(t_fork *fork)
{
	pthread_mutex_lock(fork->mutex);
}

void	fork_drop(t_fork *fork)
{
	pthread_mutex_unlock(fork->mutex);
}
