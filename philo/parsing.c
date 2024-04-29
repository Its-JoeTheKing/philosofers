/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrfig <aerrfig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 14:29:20 by aerrfig           #+#    #+#             */
/*   Updated: 2024/04/26 16:34:09 by aerrfig          ###   ########.fr       */
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

int	check_input(char **str, int ac)
{
	int	i;

	i = 1;
	if (ac < 5 || ac > 6)
		return (0);
	while (i < ac)
	{
		if (!check_str(str[i]))
			return (0);
		if (i == 1 && (ft_atoi(str[i]).num > PHILO_MAX))
			return (0);
		if (ft_atoi(str[i]).is_flow == 1
			|| (ft_atoi(str[i]).num <= 0 && i != 5))
			return (0);
		if ((i > 1 && i < 5) && ft_atoi(str[i]).num < 60)
			return (0);
		i++;
	}
	return (1);
}
