/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrfig <aerrfig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:53:11 by aerrfig           #+#    #+#             */
/*   Updated: 2024/04/25 15:44:42 by aerrfig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_all_ates(t_philo *philos)
{
	int	i;

	i = 0;
	if (philos[0].max_meals == 0)
		return (philos[0].num_of_philos);
	while ((i < philos[0].num_of_philos)
		&& (philos[i].max_meals <= philos[i].meals_eaten))
		i++;
	return ((i == philos[0].num_of_philos));
}

void	raise_flag(t_program *data, int i, int dead)
{
	if (dead)
		write_message(&data->philos[i], "died");
	pthread_mutex_lock(data->philos[i].dead_lock);
	data->dead_flag = 1;
	pthread_mutex_unlock(data->philos[i].dead_lock);
	pthread_mutex_unlock(data->philos[i].meal_lock);
}

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
	int			i;
	size_t		time;

	data = (t_program *)ph;
	while (1)
	{
		i = 0;
		while (i < data->philos[0].num_of_philos)
		{
			time = timestamp() - data->philos[i].last_meal;
			pthread_mutex_lock(data->philos[i].meal_lock);
			if (time > data->philos[i].time_to_die || check_all_ates(data->philos))
			{
				raise_flag(data, i, (time > data->philos[i].time_to_die));
				return ((void *)0);
			}
			pthread_mutex_unlock(data->philos[i].meal_lock);
			i++;
		}
	}
	return (0);
}
