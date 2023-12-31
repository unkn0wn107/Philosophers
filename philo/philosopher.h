/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 22:45:15 by agaley            #+#    #+#             */
/*   Updated: 2023/12/14 02:26:14 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct s_simu	t_simu;
typedef struct s_philo	t_philo;
typedef pthread_mutex_t	t_fork;

// Args parsing
typedef struct s_args
{
	int	num_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	min_eats;
}t_args;
void		args_init(t_simu *simu, char **argv, int argc);
int			args_are_valid(t_simu *simu, char **argv, int argc);

// Forks
void		forks_init(t_simu *simu);
void		forks_destroy(t_simu *simu);
void		fork_pick(t_fork *fork, t_philo *philo);
void		fork_drop(t_fork *fork);

// Philosopher
typedef struct s_philo
{
	int				id;
	int				num_eats;
	int				time_to_sleep;
	int				dead;
	long long		last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	mtx;
	t_fork			*l_fork;
	t_fork			*r_fork;
	t_simu			*simu;
}t_philo;
void		philos_init(t_simu *simu);
void		philo_init(t_simu *simu, int i);
void		philo_eat(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		*philo_cycle(void *arg);

// Philosopher checking
void		check_philos(t_simu *simu);
int			philo_is_dead(t_philo *philo);
# define ODD 1
# define EVEN 0

// Simulation
typedef struct s_simu
{
	t_args			*args;
	t_philo			*philos;
	t_fork			*forks;
	pthread_mutex_t	log_mtx;
	pthread_mutex_t	sync_mtx;
	int				nb_thrds_odd;
	int				nb_thrds_even;
	int				nb_forks;
	int				nb_philos;
	int				nb_phi_mtx;
	int				is_over;
	long long		start_time;
}t_simu;
void		simu_init(t_simu *simu);
void		simu_destroy(t_simu *simu, int error);
void		simu_run(t_simu *simu);
void		simu_set_over(t_simu *simu);
int			simu_is_over(t_simu *simu);
# define ERR 1
# define OK 0

// Logger
void		logger_init(pthread_mutex_t *sync_mtxt);
void		logger_destroy(pthread_mutex_t *sync_mtxt);
void		log_event(t_philo *philo, int event);
# define E_PICK_FORK 0
# define E_EAT 1
# define E_SLEEP 2
# define E_THINK 3
# define E_DIED 4

// Utils
long long	ft_time(void);
void		ft_msleep(t_simu *simu, int time);
int			ft_atoi(const char *str);
char		*ft_itoa(int nbr);
int			ft_strcmp(char *s1, char *s2);

#endif
