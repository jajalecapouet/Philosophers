/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <njaros@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 15:22:52 by njaros            #+#    #+#             */
/*   Updated: 2022/05/06 09:48:08 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_fork_lst	*new_fork(int i, t_law *law)
{
	t_fork_lst	*new;

	new = malloc(sizeof(t_fork_lst));
	if (!new)
		return (NULL);
	new->nb = i + 1;
	new->ttd = law->time_to_die;
	new->tte = law->time_to_eat;
	new->tts = law->time_to_sleep;
	new->eat_n = law->eat_number;
	new->usleep_val = law->philo_number * 25;
	new->enable = 1;
	new->count_eat = 0;
	new->next = NULL;
	return (new);
}

void	lst_forkadd_back(t_fork_lst **lst, t_fork_lst *new)
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

int	je_mange(t_fork_lst *f1, t_fork_lst *f2, t_time *tps)
{
	int	took_the_1;
	int	took_the_2;

	took_the_1 = 0;
	took_the_2 = 0;
	while (!took_the_1 || !took_the_2)
	{
		if (!val_read_law(f1->law, OK)
			|| us(tps->last_eat, tps->current) >= f1->ttd)
			return (1);
		if (!took_the_1)
			val_write_fork(f1, 0, &took_the_1, tps);
		if (!took_the_2)
			val_write_fork_next(f1, &took_the_2, tps);
		gettimeofday(&tps->current, NULL);
		usleep(f1->usleep_val);
	}
	keskifou(tps, f1->nb, BLEU"is eating\n"N, f1->law);
	f1->count_eat++;
	gettimeofday(&tps->last_eat, NULL);
	usleep_tricks(f1, f1->tte);
	gettimeofday(&tps->current, NULL);
	return (j_ai_fini(f1, f2, tps));
}

int	j_ai_fini(t_fork_lst *f1, t_fork_lst *f2, t_time *tps)
{
	val_write_fork(f1, 1, NULL, NULL);
	val_write_fork(f2, 1, NULL, NULL);
	if (f1->count_eat == f1->eat_n)
		val_write_law(f1, 1, NULL);
	if (val_read_law(f1->law, OK))
		je_dors(f1, tps);
	return (0);
}
