/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 22:44:51 by agaley            #+#    #+#             */
/*   Updated: 2023/12/12 20:13:51 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	log_event(t_philo *philo, int event)
{
	int		is_over;
	char	*msg[5];

	msg[E_PICK_FORK] = "has taken a fork";
	msg[E_EAT] = "is eating";
	msg[E_SLEEP] = "is sleeping";
	msg[E_THINK] = "is thinking";
	msg[E_DIED] = "died";
	pthread_mutex_lock(&philo->simu->sync_mtx);
	is_over = philo->simu->is_over;
	pthread_mutex_unlock(&philo->simu->sync_mtx);
	pthread_mutex_lock(&philo->simu->log_mtx);
	if (!is_over || event == E_DIED)
		printf("%lld %d %s\n", ft_time() - philo->simu->start_time,
			philo->id, msg[event]);
	pthread_mutex_unlock(&philo->simu->log_mtx);
}
