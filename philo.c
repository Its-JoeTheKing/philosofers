/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrfig <aerrfig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:53:11 by aerrfig           #+#    #+#             */
/*   Updated: 2024/04/18 16:51:38 by aerrfig          ###   ########.fr       */
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
	pthread_create(&monitor, NULL, monitoring, &program);
	while (i < ft_atoi(argv[1]).num)
	{
		pthread_create(&philos[i].thread, NULL, routine, &philos[i]);
		i++;
	}
	i = 0;
	while (i < ft_atoi(argv[1]).num)
	{
		pthread_detach(philos[i].thread);
		i++;
	}
	pthread_join(monitor, NULL);
	pthread_mutex_destroy(&program.dead_lock);
	pthread_mutex_destroy(&program.meal_lock);
	pthread_mutex_destroy(&program.write_lock);
	i = 0;
	while (i)
	{
		pthread_mutex_destroy(&program.forks[i]);
		i++;
	}
	return (0);
}

void	*monitoring(void *ph)
{
	t_program	*data;
	int	i;

	data = (t_program *)ph;
	i = 0;
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
				write_message(&data->philos[i], "is dead");
				return (0);
			}
			pthread_mutex_unlock(data->philos[i].meal_lock);
			i++;
		}
	}
	return (0);
}
