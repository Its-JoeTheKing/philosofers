/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrfig <aerrfig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:53:11 by aerrfig           #+#    #+#             */
/*   Updated: 2024/08/10 10:58:16 by aerrfig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_philo			*philos;
	t_program		program;
	int				i;

	(1) && (i = -1, philos = NULL);
	if (!check_input(argv, argc, &philos))
		return (-1);
	init_program(argv, &program);
	init_philos(philos, argv, &program);
	program.philos = philos;
	while (++i < philos[0].num_of_philos)
	{
		if (pthread_create(&philos[i].thread, NULL, routine,
				&philos[i]) != 0)
			return (destroy_all(&program), -1);
	}
	monitoring(&program);
	i = -1;
	while (++i < philos[0].num_of_philos)
	{
		if (pthread_join(philos[i].thread, NULL) != 0)
			return (destroy_all(&program), 0);
	}
	destroy_all(&program);
	return (0);
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
