/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrfig <aerrfig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:53:11 by aerrfig           #+#    #+#             */
/*   Updated: 2024/04/02 16:59:28 by aerrfig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(char *str, t_philo *philo, int id)
{
	size_t	time;

	// pthread_mutex_lock(philo->write_lock);
	time = timestamp() - philo->start_time;
	printf("%zu %d %s\n", time, id, str);
	// pthread_mutex_unlock(philo->write_lock);
}

void	*dream(void	*ph)
{
	t_philo	*philo;
	philo = (t_philo *)ph;
	print_message("philo is sleeping", philo, philo->id);
	return (0);
}
void	*eating(void	*ph)
{
	t_philo	*philo;
	philo = (t_philo *)ph;
	print_message("philo is eating", philo, philo->id);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_philo			philos[PHILO_MAX];
	t_program		program;
	pthread_mutex_t	forks[PHILO_MAX];

	if (!check_input(argv, argc))
		return (-1);
	init_prog(philos, &program, forks);
	init_philos(philos, forks, argv, &program);
	int i = 0;
	while (i < ft_atoi(argv[1]).num)
	{
		pthread_create(&philos[i].thread, NULL, dream, &philos[i]);
		pthread_create(&philos[i].thread, NULL, eating, &philos[i]);
		i++;
	}
	i = 0;
	while (i < ft_atoi(argv[1]).num)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}
