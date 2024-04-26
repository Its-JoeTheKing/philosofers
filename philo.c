/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrfig <aerrfig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:53:11 by aerrfig           #+#    #+#             */
/*   Updated: 2024/04/26 11:24:41 by aerrfig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_philo			philos[PHILO_MAX];
	t_program		program;
	int				i;

	i = 0;
	if (!check_input(argv, argc))
		return (-1);
	init_program(argv, &program);
	init_philos(philos, argv, &program);
	program.philos = philos;
	starting_sim(&program);
	destroy_all(&program);
	return (0);
}

void	starting_sim(t_program *data)
{
	int				i;
	pthread_t		monitor;

	i = 0;
	while (i < data->philos[0].num_of_philos)
	{
		pthread_create(&data->philos[i].thread, NULL, routine,
			&data->philos[i]);
		i++;
	}
	pthread_create(&monitor, NULL, monitoring, data);
	i = 0;
	while (i < data->philos[0].num_of_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitor, NULL);
}

void	destroy_all(t_program *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->dead_lock);
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->meal_lock);
	while (i < data->philos[0].num_of_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
}
