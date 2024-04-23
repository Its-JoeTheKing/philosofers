/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:53:11 by aerrfig           #+#    #+#             */
/*   Updated: 2024/04/23 10:59:44 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_philo			philos[PHILO_MAX];
	t_program		program;
	pthread_t		monitor;
	int				i;
	
	i = 0;
	if (!check_input(argv, argc))
		return (-1);
	init_program(argv, &program);
	init_philos(philos, argv, &program);
	while (i < philos[0].num_of_philos)
	{
		pthread_create(&philos[i].thread, NULL, routine, &philos[i]);
		i++;
	}
	pthread_create(&monitor, NULL, monitoring, &program);
	i = 0;
	while (i < philos[0].num_of_philos)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitor, NULL);
	return (0);
}

void	*monitoring(void *ph)
{
	t_program	*data;
	int	i;

	data = (t_program *)ph;
	while (15)
	{
		i = 0;
		while (i < data->philos[0].num_of_philos)
		{
			pthread_mutex_lock(data->philos[i].meal_lock);
			if (timestamp() - data->philos[i].last_meal > data->philos[i].time_to_die)
			{
				pthread_mutex_lock(data->philos[i].dead_lock);
				data->dead_flag = 1;
				pthread_mutex_unlock(data->philos[i].dead_lock);
				pthread_mutex_lock(data->philos[i].write_lock);
				printf("%ld %d is dead\n", timestamp() - data->philos[i].start_time, data->philos[0].id);
				pthread_mutex_unlock(data->philos[i].write_lock);
				return (pthread_mutex_unlock(data->philos[i].meal_lock), (void *)0);
			}
			pthread_mutex_unlock(data->philos[i].meal_lock);
			i++;
		}
	}
	return (0);
}
