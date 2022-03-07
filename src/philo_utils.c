/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 10:53:32 by njaros            #+#    #+#             */
/*   Updated: 2022/03/07 17:48:57 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	insert_mutex_law(fork_lst *lst, law *law)
{
	int				boucle;
	int				secure;
	fork_lst		*first;
	pthread_mutex_t	mutex;

	secure = -1;
	boucle = 0;
	first = lst;
	while (!(boucle++ && first == lst) && ++secure >= 0)
	{
		if (pthread_mutex_init(&mutex, NULL))
		{
			while (--secure >= 0)
			{
				pthread_mutex_destroy(&first->mutex);
				first = first->next;
			}
			return (11);
		}
		lst->mutex = mutex;
		lst->law = law;
		lst = lst->next;
	}
	return (0);
}

int	crea_forks_phils(fork_lst **forks, pthread_t **phils, int nb, law *law)
{
	int			i;
	fork_lst	*first;
	fork_lst	*new;

	first = NULL;
	*forks = NULL;
	*phils = malloc(sizeof(pthread_t) * nb);
	if (!forks)
		return (11);
	i = -1;
	while (++i < nb)
	{
		new = new_fork(i);
		if (!new)
			return (11);
		lst_forkadd_back(forks, new);
		if (!first)
			first = *forks;
	}
	(*forks)->next = first;
	*forks = first;
	return (insert_mutex_law(*forks, law));
}

void	*philo_handler(void *arg)
{
	t_time		tps;
	fork_lst	*fork;
	int			think;
	int			dididie;

	think = 0;
	dididie = 0;
	fork = (fork_lst *)arg;
	init_time(&tps);
	while (fork->law->all_alive && dididie <= fork->law->time_to_die)
	{
		if (fork->enable && fork->next->enable)
		{
			think = je_mange(fork, fork->next, &tps);
			je_dors(fork, &tps);
		}
		else 
				think = je_pense(fork->nb, &tps, think);
		dididie = us(tps.last_eat, tps.current);
	}
	if (dididie >= fork->law->time_to_die)
	{
		keskifou(&tps, fork->nb, ROUGE"died\n"NORMAL);
		fork->law->all_alive = 0;
	}
	return (NULL);
}