/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 11:45:58 by njaros            #+#    #+#             */
/*   Updated: 2022/03/07 17:38:38 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// keskifou nous dit ce que fout un philo a quel moment
int	keskifou(t_time *tps, int philo, char *str)
{
	int	time;

	gettimeofday(&tps->current, NULL);
	time = ms(tps->start, tps->current);
	return (printf("%d %d %s", time, philo, str));
}

void	je_dors(fork_lst *fork, t_time *tps)
{
	keskifou(tps, fork->nb, "is sleeping\n");
	if (fork->law->time_to_die > fork->law->time_to_sleep)
		usleep(fork->law->time_to_sleep);
	else
		usleep(fork->law->time_to_die);
}

int	je_pense(int philo, t_time *tps, int think)
{
	if (!think)
		keskifou(tps, philo, "is thinking\n");
	else
		gettimeofday(&tps->current, NULL);
	return (1);
}