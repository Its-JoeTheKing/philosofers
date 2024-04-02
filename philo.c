/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrfig <aerrfig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:53:11 by aerrfig           #+#    #+#             */
/*   Updated: 2024/04/02 11:31:26 by aerrfig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_philo			*philos[PHILO_MAX];
	t_program		program;
	pthread_mutex_t	*forks[PHILO_MAX];

	if (!check_input(argv, argc))
		return (-1);
	
}
