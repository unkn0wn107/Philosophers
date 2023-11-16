/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 22:43:24 by agaley            #+#    #+#             */
/*   Updated: 2023/11/16 01:24:58 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

// Function to initialize a fork
void	fork_init(t_fork *fork)
{
	pthread_mutex_init(&fork->mutex, NULL);
}

// Function to destroy a fork
void	fork_destroy(t_fork *fork)
{
	pthread_mutex_destroy(&fork->mutex);
}

// Function to pick up a fork
void	fork_pick(t_fork *fork)
{
	pthread_mutex_lock(&fork->mutex);
}

// Function to put down a fork
void	fork_drop(t_fork *fork)
{
	pthread_mutex_unlock(&fork->mutex);
}
