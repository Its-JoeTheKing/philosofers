/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrfig <aerrfig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:07:17 by aerrfig           #+#    #+#             */
/*   Updated: 2024/04/02 16:01:32 by aerrfig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	init_philos(t_philo *philos, pthread_mutex_t *forks, char **argv, t_program *program)
{
	int	i;

	i = 0;
	while (i < ft_atoi(argv[1]).num)
	{
		philos[i].num_of_philos = ft_atoi(argv[1]).num;
		philos[i].time_to_die = ft_atoi(argv[2]).num;
		philos[i].time_to_eat = ft_atoi(argv[3]).num;
		philos[i].time_to_sleep = ft_atoi(argv[4]).num;
		philos[i].id = i + 1;
		philos[i].meals_eaten = 0;
		philos[i].eating = 0;
		philos[i].l_fork = &forks[i];
		philos[i].r_fork = &forks[philos[i].num_of_philos - i];
		philos[i].dead_lock = &program->dead_lock;
		philos[i].meal_lock = &program->meal_lock;
		philos[i].write_lock = &program->write_lock;
		philos[i].start_time = timestamp();
		philos[i].last_meal = timestamp();
		i++;
	}
}

void	init_prog(t_philo *philos, t_program *program, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	pthread_mutex_init(&program->dead_lock, NULL);
	pthread_mutex_init(&program->write_lock, NULL);
	pthread_mutex_init(&program->meal_lock, NULL);
	program->philos = philos;
	program->dead_flag = 0;
	while (i < philos->num_of_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}
