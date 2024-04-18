/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrfig <aerrfig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:03:37 by aerrfig           #+#    #+#             */
/*   Updated: 2024/04/18 16:43:51 by aerrfig          ###   ########.fr       */
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
	write_message(philo, "is thinking");
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	write_message(philo, "has taken a fork");
	pthread_mutex_lock(philo->l_fork);
	write_message(philo, "has taken a fork");
	write_message(philo, "is eating");
	// philo->eating = 1;
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = timestamp();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	// philo->eating = 0;
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	*routine(void *ph)
{
	t_philo	*philo;
	int		is_dead;

	philo = (t_philo *)ph;
	is_dead = 0;
	if (philo->id % 2 == 0)
		ft_usleep(15);
	while (!is_dead)
	{
		pthread_mutex_lock(philo->dead_lock);
		is_dead = *(philo->dead);
		pthread_mutex_unlock(philo->dead_lock);
		eat(philo);
		dream(philo);
	}
	return (0);
}
