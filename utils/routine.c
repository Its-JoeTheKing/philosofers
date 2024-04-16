/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrfig <aerrfig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:03:37 by aerrfig           #+#    #+#             */
/*   Updated: 2024/04/16 18:41:13 by aerrfig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	write_message(t_philo *philo, char *msg)
{
	pthread_mutex_lock(philo->write_lock);
	printf("%ld %d %s\n", timestamp() - philo->start_time, philo->id, msg);
	pthread_mutex_unlock(philo->write_lock);
}

void	dream(t_philo *philo)
{
	write_message(philo, "is sleeping");
	ft_usleep(philo->time_to_sleep);
}

void	think(t_philo *philo)
{
	write_message(philo, "is thinking");
	ft_usleep(philo->time_to_sleep);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	write_message(philo, "has taken a fork");
	pthread_mutex_lock(philo->l_fork);
	write_message(philo, "has taken a fork");
	write_message(philo, "is eating");
	philo->eating = 1;
	pthread_mutex_lock(philo->meal_lock);
	philo->meals_eaten++;
	philo->last_meal = timestamp();
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	philo->eating = 0;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	*routine(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (*(philo->dead) == 0)
	{
		eat(philo);
		dream(philo);
		think(philo);
	}
	return (0);
}
