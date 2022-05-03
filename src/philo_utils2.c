/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <njaros@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 15:22:52 by njaros            #+#    #+#             */
/*   Updated: 2022/05/03 19:31:15 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

fork_lst	*new_fork(int i)
{
	fork_lst	*new;

	new = malloc(sizeof(fork_lst));
	if (!new)
		return (NULL);
	new->nb = i + 1;
	new->enable = 1;
	new->count_eat = 0;
	new->next = NULL;
	return (new);
}

void	lst_forkadd_back(fork_lst **lst, fork_lst *new)
{
	if (!*lst)
		*lst = new;
	else
	{
		while ((*lst)->next)
			*lst = (*lst)->next;
		(*lst)->next = new;
		*lst = new;
	}
}

int	je_mange(fork_lst *fourchette1, fork_lst *fourchette2, t_time *tps)
{
	int	dispo1;
	int dispo2;

	dispo1 = 0;
	dispo2 = 0;
	//while (!fourchette1->enable && !fourchette2->enable && (fourchette1->next != fourchette1))
	while ((!dispo1 || !dispo2) && (fourchette1->next != fourchette1))
	{
		pthread_mutex_lock(&fourchette1->mutex);
		if (!dispo1)
		{
			if (fourchette1->enable)
			{
				fourchette1->enable = 0;
				dispo1 = 1;
			}
		}
		pthread_mutex_unlock(&fourchette1->mutex);
		pthread_mutex_lock(&fourchette2->mutex);
		if (!dispo2)
		{
			if (fourchette2->enable)
			{
				fourchette2->enable = 0;
				dispo2 = 1;
			}
		}
		pthread_mutex_unlock(&fourchette2->mutex);
		gettimeofday(&tps->current, NULL);
		pthread_mutex_lock(&fourchette1->law->read);
		if (!fourchette1->law->all_alive || us(tps->last_eat, tps->current) >= fourchette1->law->time_to_die
				|| !fourchette1->law->philo_number)
		{
			return (1);
			pthread_mutex_unlock(&fourchette1->law->read);
		}
		pthread_mutex_unlock(&fourchette1->law->read);
	}
	keskifou(tps, fourchette1->nb, BLEUCLAIR"has taken a fork\n"NORMAL, fourchette1->law);
	keskifou(tps, fourchette1->nb, BLEUCLAIR"has taken a fork\n"NORMAL, fourchette1->law);
	keskifou(tps, fourchette1->nb, BLEU"is eating\n"NORMAL, fourchette1->law);
	fourchette1->count_eat++;
	gettimeofday(&tps->last_eat, NULL);
	usleep_tricks(fourchette1->law, fourchette1->law->time_to_eat);
	gettimeofday(&tps->current, NULL);
	return (j_ai_fini(fourchette1, fourchette2, tps));
}

int	j_ai_fini(fork_lst *fourchette1, fork_lst *fourchette2, t_time *tps)
{
	int	dodo;

	dodo = 0;
	pthread_mutex_lock(&fourchette1->mutex);
	fourchette1->enable = 1;
	pthread_mutex_unlock(&fourchette1->mutex);
	pthread_mutex_lock(&fourchette2->mutex);
	fourchette2->enable = 1;
	pthread_mutex_unlock(&fourchette2->mutex);
	pthread_mutex_lock(&fourchette1->law->read);
	if (fourchette1->count_eat == fourchette1->law->eat_number)
	{
		pthread_mutex_lock(&fourchette1->law->finish);
		fourchette1->law->philo_number--;
		pthread_mutex_unlock(&fourchette1->law->finish);
	}
	if (fourchette1->law->all_alive && fourchette1->law->philo_number)
		dodo = 1;
	pthread_mutex_unlock(&fourchette1->law->read);
	if (dodo)
		je_dors(fourchette1, tps);
	return (0);
}