/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrfig <aerrfig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:48:41 by aerrfig           #+#    #+#             */
/*   Updated: 2024/04/02 15:22:23 by aerrfig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	eat(void *d)
{
	t_philo	philo;

	philo = (t_philo)d;
	pthread_mutex_lock(philo.meal_lock);	
	pthread_mutex_lock(philo.r_fork);	
	pthread_mutex_lock(philo.l_fork);
	ft_usleep(1);
	printf("%d is eating", philo.id);
	pthread_mutex_unlock(philo.meal_lock);
	pthread_mutex_unlock(philo.r_fork);
	pthread_mutex_unlock(philo.l_fork);
}
