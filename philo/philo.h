/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrfig <aerrfig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 09:44:05 by aerrfig           #+#    #+#             */
/*   Updated: 2024/08/12 11:09:00 by aerrfig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

# ifndef PHILO_MAX
#  define PHILO_MAX 200
# endif

typedef struct s_num
{
	long long	num;
	int			is_flow;
}	t_num;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				max_meals;
	int				meals_eaten;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				num_of_philos;
	int				num_times_to_eat;
	int				*dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}					t_philo;

typedef struct s_program
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
	pthread_mutex_t	*forks;
}					t_program;

size_t	timestamp(void);
void	ft_usleep(int n);
int		check_input(char **str, int ac, t_philo **philos);
t_num	ft_atoi(const char *str);
void	init_program(char **argv, t_program *pro);
void	init_philos(t_philo *philos, char **argv, t_program *program);
void	*routine(void *ph);
int		monitoring(t_program *data);
void	write_message(t_philo *philo, char *msg);
int		check_death(t_philo *philo);
int		check_all_ates(t_philo *philos);
void	raise_flag(t_program *data, int i, int dead);
void	destroy_all(t_program *data);

#endif