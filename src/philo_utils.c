/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <njaros@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 10:53:32 by njaros            #+#    #+#             */
/*   Updated: 2022/05/03 19:26:25 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	insert_mutex_law(fork_lst *lst, law *law)
{
	int				boucle;
	int				secure;
	fork_lst		*first;

	secure = -1;
	boucle = 0;
	first = lst;
	while (!(boucle++ && first == lst) && ++secure >= 0)
	{
		if (pthread_mutex_init(&lst->mutex, NULL) || pthread_mutex_init(&lst->mutex_read, NULL))
		{
			while (--secure >= 0)
			{
				pthread_mutex_destroy(&first->mutex);
				first = first->next;
			}
			return (12);
		}
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

void	init_philo(t_time *tps, fork_lst *fork)
{
	int	rdy;

	rdy = 0;
	pthread_mutex_lock(&fork->law->ready);
	fork->law->ready_count++;
	pthread_mutex_unlock(&fork->law->ready);
	if (fork->nb == 1)
	{
		while (!rdy)
		{
			pthread_mutex_lock(&fork->law->ready);
			if (fork->law->ready_count != fork->law->philo_number)
				usleep(100);
			else
				rdy = 1;
			pthread_mutex_unlock(&fork->law->ready);
		}
		gettimeofday(&fork->law->start, NULL);
	}
	else
	{
		while (!fork->law->start.tv_sec)
			;
	}
	init_time(tps, fork->law->start);
	if (fork->nb % 2 == 1)
		usleep(100);
}

void	*philo_handler(void *arg)
{
	t_time		tps;
	fork_lst	*fork;
	int			think;
	int			dididie;

	think = 1;
	dididie = 0;
	fork = (fork_lst *)arg;
	init_philo(&tps, fork);
	while (fork->law->all_alive && dididie <= fork->law->time_to_die
				&& fork->law->philo_number)
	{
		if (think)
			think = je_mange(fork, fork->next, &tps);
		else if (dididie < fork->law->time_to_die)
			think = je_pense(fork->nb, &tps, think, fork->law);
		dididie = us(tps.last_eat, tps.current);
	}
	if (dididie >= fork->law->time_to_die)
	{
		pthread_mutex_lock(&fork->law->rip_mut);
		if (fork->law->all_alive)
		{
			keskifou(&tps, fork->nb, ROUGE"died\n"NORMAL, fork->law);
			fork->law->all_alive = 0;
		}
		pthread_mutex_unlock(&fork->law->rip_mut);
	}
	return (NULL);
}
