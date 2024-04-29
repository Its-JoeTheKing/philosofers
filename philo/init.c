/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrfig <aerrfig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:36:19 by aerrfig           #+#    #+#             */
/*   Updated: 2024/04/26 16:34:17 by aerrfig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_program(char **argv, t_program *pro)
{
	int	i;

	i = 0;
	pro->dead_flag = 0;
	pthread_mutex_init(&pro->dead_lock, NULL);
	pthread_mutex_init(&pro->meal_lock, NULL);
	pthread_mutex_init(&pro->write_lock, NULL);
	while (i < ft_atoi(argv[1]).num)
	{
		pthread_mutex_init(&pro->forks[i], NULL);
		i++;
	}
}

void	init_philos(t_philo *philos, char **argv, t_program *program)
{
	int	i;

	i = -1;
	while (++i < ft_atoi(argv[1]).num)
	{
		philos[i].num_of_philos = ft_atoi(argv[1]).num;
		philos[i].time_to_die = ft_atoi(argv[2]).num;
		philos[i].time_to_eat = ft_atoi(argv[3]).num;
		philos[i].time_to_sleep = ft_atoi(argv[4]).num;
		philos[i].max_meals = ft_atoi(argv[5]).num;
		philos[i].start_time = timestamp();
		philos[i].last_meal = timestamp();
		philos[i].meals_eaten = 0;
		philos[i].eating = 0;
		philos[i].id = i + 1;
		philos[i].dead = &program->dead_flag;
		philos[i].l_fork = &program->forks[i];
		if (i == 0)
			philos[i].r_fork = &program->forks[philos[i].num_of_philos - 1];
		else
			philos[i].r_fork = &program->forks[i - 1];
		philos[i].write_lock = &program->write_lock;
		philos[i].dead_lock = &program->dead_lock;
		philos[i].meal_lock = &program->meal_lock;
	}
}
