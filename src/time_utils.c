/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <njaros@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 13:53:44 by njaros            #+#    #+#             */
/*   Updated: 2022/05/03 18:06:12 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// keskifou nous dit ce que fout un philo a quel moment

int	ms(struct timeval t1, struct timeval t2)
{
	int	temps_ms;

	temps_ms = (t2.tv_sec - t1.tv_sec) * 1000;
	temps_ms += (t2.tv_usec - t1.tv_usec) / 1000;
	return (temps_ms);
}

int	us(struct timeval t1, struct timeval t2)
{
	int	temps_us;

	temps_us = (t2.tv_sec - t1.tv_sec) * 1000000;
	temps_us += (t2.tv_usec - t1.tv_usec);
	return (temps_us);
}

int	keskifou(t_time *tps, int philo, char *str, law *law)
{
	int	time;

	pthread_mutex_lock(&law->write);
	gettimeofday(&tps->current, NULL);
	time = ms(tps->start, tps->current);
	printf("%d %d %s", time, philo, str);
	pthread_mutex_unlock(&law->write);
	return (0);
}

void	init_time(t_time *tps, struct timeval start)
{
	gettimeofday(&tps->current, NULL);
	gettimeofday(&tps->last_eat, NULL);
	tps->start = start;
	tps->nbr_eat = 0;
}

void	usleep_tricks(law *law, int time)
{
	struct timeval	t1;
	struct timeval	t2;

	gettimeofday(&t1, NULL);
	gettimeofday(&t2, NULL);
	while (us(t1, t2) < time && law->philo_number && law->all_alive)
	{
		usleep(law->usleep_val);
		gettimeofday(&t2, NULL);
	}
}
