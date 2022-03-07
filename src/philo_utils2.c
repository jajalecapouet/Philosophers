/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 15:22:52 by njaros            #+#    #+#             */
/*   Updated: 2022/03/07 17:54:17 by njaros           ###   ########lyon.fr   */
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

void	init_time(t_time *tps)
{
	gettimeofday(&tps->current, NULL);
	gettimeofday(&tps->last_eat, NULL);
	gettimeofday(&tps->start, NULL);
}

int	je_mange(fork_lst *fourchette1, fork_lst *fourchette2, t_time *tps)
{
	int	i;

	i = pthread_mutex_lock(&fourchette1->mutex);
	if (i) //des idées de génie
		return (i);
	fourchette1->enable = 0;
	while (!fourchette2->enable)
	{
		gettimeofday(&tps->current, NULL);
		if (us(tps->last_eat, tps->current) >= fourchette1->law->time_to_die)
			return (0);
	}
	keskifou(tps, fourchette1->nb, BLEUCLAIR"has taken a fork\n"NORMAL);
	i = pthread_mutex_lock(&fourchette2->mutex);
	if (i)
		return (i);
	fourchette2->enable = 0;
	keskifou(tps, fourchette1->nb, BLEUCLAIR"has taken a fork\n"NORMAL);
	keskifou(tps, fourchette1->nb, BLEU"is eating\n"NORMAL);
	usleep(fourchette1->law->time_to_eat);
	gettimeofday(&tps->current, NULL);
	gettimeofday(&tps->last_eat, NULL);
	return (j_ai_fini(fourchette1, fourchette2));
}

int	j_ai_fini(fork_lst *fourchette1, fork_lst *fourchette2)
{
	int	i;

	fourchette1->enable = 1;
	fourchette2->enable = 1;
	i = pthread_mutex_unlock(&fourchette1->mutex);
	if (i)
		return (i);
	return (pthread_mutex_unlock(&fourchette2->mutex));
}