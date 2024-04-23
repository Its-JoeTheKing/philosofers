/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:03:37 by aerrfig           #+#    #+#             */
/*   Updated: 2024/04/23 10:57:51 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	write_message(t_philo *philo, char *msg)
{
	pthread_mutex_lock(philo->write_lock);
	if (!check_death(philo))
		printf("%ld %d %s\n", timestamp() - philo->start_time, philo->id, msg);
	pthread_mutex_unlock(philo->write_lock);
}

void	dream(t_philo *philo)
{
	write_message(philo, "is sleeping");
	ft_usleep(philo->time_to_sleep);
	write_message(philo, "is thinking");
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	write_message(philo, "has taken a fork");
	pthread_mutex_lock(philo->l_fork);
	write_message(philo, "has taken a fork");
	write_message(philo, "is eating");
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = timestamp();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

int	check_death(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*(philo->dead))
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	*routine(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	if (philo->id % 2 == 0)
		ft_usleep(100);
	while (!check_death(philo))
	{
		eat(philo);
		dream(philo);
	}
	return (0);
}
