/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 19:20:59 by agaley            #+#    #+#             */
/*   Updated: 2023/12/13 19:09:47 by agaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

long long	ft_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (long long)1000) + (tv.tv_usec / 1000));
}

void	ft_msleep(t_simu *simu, int time)
{
	int			is_over;
	long long	start;

	is_over = 0;
	start = ft_time();
	while (ft_time() - start < time && !is_over)
	{
		pthread_mutex_lock(&simu->sync_mtx);
		is_over = simu->is_over;
		pthread_mutex_unlock(&simu->sync_mtx);
		usleep(1000);
	}
}
