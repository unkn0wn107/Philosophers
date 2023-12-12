/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 22:45:15 by agaley            #+#    #+#             */
/*   Updated: 2023/12/12 20:17:55 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <pthread.h>

# define E_PICK_FORK 0
# define E_EAT 1
# define E_SLEEP 2
# define E_THINK 3
# define E_DIED 4

typedef struct s_args
{
	int	num_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	min_eats;
}t_args;

typedef struct s_fork
{
	pthread_mutex_t	*mutex;
}t_fork;

typedef struct s_simu	t_simu;

typedef struct s_philo
{
	int				id;
	int				num_eats;
	int				time_to_sleep;
	int				dead;
	long long		last_meal_time;
	pthread_t		thread;
	t_fork			*l_fork;
	t_fork			*r_fork;
	t_simu			*simu;
}t_philo;

typedef struct s_simu
{
	t_args			*args;
	t_philo			**philos;
	t_fork			**forks;
	pthread_mutex_t	log_mtx;
	pthread_mutex_t	sync_mtx;
	int				nb_threads;
	int				nb_forks;
	int				is_over;
	long long		start_time;
}t_simu;

void		args_init(t_simu *simu, char **argv, int argc);
int			args_are_valid(t_simu *simu, char **argv, int argc);

int			fork_init(t_fork *fork);
void		fork_destroy(t_fork *fork);
void		fork_pick(t_fork *fork);
void		fork_drop(t_fork *fork);

// Philosopher
void		philo_init(t_simu *simu, int i);
void		philo_eat(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		philo_think(t_philo *philo);
void		philo_dies(t_philo *philo);

// Philosopher checking
int			is_philo_alive(t_philo *philo);
int			has_eaten_enough(t_philo *philo);

void		forks_init(t_simu *simu);
void		philos_init(t_simu *simu);
void		simu_init(t_simu *simu);
void		simu_destroy(t_simu *simu, int error);
void		simu_run(t_simu *simu);
void		simu_stop(t_simu *simu);
int			simu_is_over(t_simu *simu);

void		logger_init(pthread_mutex_t *sync_mtxt);
void		logger_destroy(pthread_mutex_t *sync_mtxt);
void		log_event(t_philo *philo, int event);

long long	ft_time(void);
void		ft_msleep(t_simu *simu, int time);
int			ft_atoi(const char *str);
char		*ft_itoa(int nbr);
int			ft_strcmp(char *s1, char *s2);

#endif //PHILOSOPHER_H
