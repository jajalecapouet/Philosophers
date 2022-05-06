/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <njaros@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 09:37:09 by njaros            #+#    #+#             */
/*   Updated: 2022/05/06 09:37:09 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	val_read_law(t_law *law, int to_read)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&law->mutex_law);
	if (to_read == OK)
	{
		if (law->philo_number && law->all_alive)
		ret = 1;
	}
	else if (to_read == ALL_READY && law->philo_number == law->ready_count)
		ret = 1;
	else if (to_read == START_OK && law->start.tv_sec)
		ret = 1;
	pthread_mutex_unlock(&law->mutex_law);
	return (ret);
}

void	val_write_law(t_fork_lst *fork, int to_write, t_time *tps)
{
	pthread_mutex_lock(&fork->law->mutex_law);
	if (to_write == I_DIED)
	{
		if (fork->law->all_alive)
		{
			keskifou(tps, fork->nb, ROUGE"died\n"N, fork->law);
			fork->law->all_alive = 0;
		}
	}
	else if (to_write == COUNT_DONE)
		fork->law->philo_number -= 1;
	else if (to_write == I_RDY)
		fork->law->ready_count += 1;
	pthread_mutex_unlock(&fork->law->mutex_law);
}

void	val_write_fork(t_fork_lst *fork, int etat, int *dispo, t_time *tps)
{
	pthread_mutex_lock(&fork->mutex);
	if (etat == 0)
	{
		if (fork->enable)
		{
			fork->enable = 0;
			*dispo = 1;
			keskifou(tps, fork->nb, CYAN"has taken a fork\n"N, fork->law);
		}
	}
	else
		fork->enable = 1;
	pthread_mutex_unlock(&fork->mutex);
}

void	val_write_fork_next(t_fork_lst *fork, int *token, t_time *tps)
{
	pthread_mutex_lock(&fork->next->mutex);
	if (fork->next->enable)
	{
		fork->next->enable = 0;
		*token = 1;
		keskifou(tps, fork->nb, CYAN"has taken a fork\n"N, fork->law);
	}
	pthread_mutex_unlock(&fork->next->mutex);
}
