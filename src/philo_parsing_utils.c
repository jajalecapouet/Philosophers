/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parsing_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 11:09:57 by njaros            #+#    #+#             */
/*   Updated: 2022/03/07 15:51:01 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	int		i;
	long	r;
	int		sign;

	r = 0;
	sign = 1;
	i = 0;
	while ((nptr[i] == '\t') || (nptr[i] == '\n') || (nptr[i] == '\v')
		|| (nptr[i] == '\f') || (nptr[i] == '\r') || (nptr[i] == ' '))
		i++;
	if ((nptr[i] == '-') || (nptr[i] == '+'))
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while ((nptr[i] >= '0') && (nptr[i] <= '9'))
	{
		r = 10 * r;
		r = r + (nptr[i] - '0');
		i++;
	}
	return ((int)sign * r);
}

int	ft_isdigit(int c)
{
	if ((c >= '0') && (c <= '9'))
		return (1);
	return (0);
}

int	parsing_fill(char **to_parse, law *to_fill)
{
	int	i;

	i = -1;
	while (to_parse[++i])
	{
		if (!ft_isdigit(to_parse[i][0]))
			return (22);
	}
	to_fill->philo_number = ft_atoi(to_parse[0]);
	to_fill->time_to_die = ft_atoi(to_parse[1]) * 1000;
	to_fill->time_to_eat = ft_atoi(to_parse[2]) * 1000;
	to_fill->time_to_sleep = ft_atoi(to_parse[3]) * 1000;
	to_fill->eat_number = ft_atoi(to_parse[4]);
	to_fill->all_alive = 1;
	return (0);
}