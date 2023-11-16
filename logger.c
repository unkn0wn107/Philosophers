/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 22:44:51 by agaley            #+#    #+#             */
/*   Updated: 2023/11/16 02:14:51 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	log_event(t_philo *philo, int event)
{
	char		*msg[5];

	msg[0] = "has taken a fork";
	msg[1] = "is eating";
	msg[2] = "is sleeping";
	msg[3] = "is thinking";
	msg[4] = "died";
	pthread_mutex_lock(philo->log_mutex);
	printf("%lld %d %s\n", ft_time(), philo->id, msg[event]);
	pthread_mutex_unlock(philo->log_mutex);
}
