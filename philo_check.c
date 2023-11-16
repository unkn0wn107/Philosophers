/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 02:19:10 by agaley            #+#    #+#             */
/*   Updated: 2023/11/16 02:44:07 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	has_eaten_enough(t_philo *philo)
{
	if (philo->args->min_eats == 0 || philo->args->min_eats < philo->num_eats)
		return (0);
	return (1);
}

int	is_philo_alive(t_philo *philo)
{
	if (ft_time() - philo->last_meal_time > philo->args->time_to_die)
		return (0);
	return (1);
}
