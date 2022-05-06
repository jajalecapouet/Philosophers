/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <njaros@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 11:45:58 by njaros            #+#    #+#             */
/*   Updated: 2022/05/06 09:29:11 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	je_dors(t_fork_lst *fork, t_time *tps)
{
	keskifou(tps, fork->nb, "is sleeping\n", fork->law);
	if (fork->ttd > fork->tts + fork->tte)
		usleep_tricks(fork, fork->tts);
	else
		usleep_tricks(fork, fork->ttd);
	gettimeofday(&tps->current, NULL);
}

int	je_pense(int philo, t_time *tps, int think, t_law *law)
{
	if (!think)
		keskifou(tps, philo, "is thinking\n", law);
	else
		gettimeofday(&tps->current, NULL);
	return (1);
}
