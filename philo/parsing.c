/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrfig <aerrfig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 14:29:20 by aerrfig           #+#    #+#             */
/*   Updated: 2024/08/10 11:31:09 by aerrfig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_num	ft_atoi(const char *str)
{
	int		i;
	t_num	res;

	i = 0;
	res.num = 0;
	res.is_flow = 0;
	if (!str)
		return ((t_num){-1, 0});
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res.num *= 10;
		res.num += str[i++] - '0';
		if (res.num > 2147483647 || res.num < -2147483648)
			res.is_flow = 1;
	}
	return ((t_num){res.num, res.is_flow});
}

int	check_str(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9'))
			return (0);
		i++;
	}
	return (1);
}

int	check_input(char **str, int ac, t_philo **philos)
{
	int	i;

	i = 1;
	if (ac < 5 || ac > 6)
		return (write(2, "invalid number of arguments", 28), 0);
	while (i < ac)
	{
		if (!check_str(str[i]))
			return (write(2, "expecting only positive numbers", 27), 0);
		if (i == 1
			&& (ft_atoi(str[i]).num > PHILO_MAX || ft_atoi(str[i]).num <= 0))
			return (write(2,
					"number of philosophers shoud be between 1 - 200", 48), 0);
		if (ft_atoi(str[i]).is_flow == 1)
			return (write(2, "invalid argument (overflow)", 40), 0);
		if ((i > 1 && i < 5) && ft_atoi(str[i]).num < 60)
			return (write(2, "times should not be lower than 60 ms", 37), 0);
		i++;
	}
	*philos = malloc(sizeof(struct s_philo) * (ft_atoi(str[1]).num + 1));
	if (!*philos)
		return (0);
	return (1);
}
