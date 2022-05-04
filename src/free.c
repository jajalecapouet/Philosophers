/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <njaros@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 15:41:44 by njaros            #+#    #+#             */
/*   Updated: 2022/05/03 18:01:38 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	forks_clear(fork_lst *lst, int context)
{
	fork_lst	*first;
	fork_lst	*temp;
	int			boucle;

	boucle = 0;
	first = lst;
	while (!(boucle && lst == first))
	{
		boucle = 1;
		temp = lst;
		lst = lst->next;
		if (context)
			pthread_mutex_destroy(&lst->mutex);
		free(temp);
	}
}

void	destroy_mutex(law *law)
{
	pthread_mutex_destroy(&law->mutex_law);
	pthread_mutex_destroy(&law->write);
}

int	freeteuse(int err, fork_lst *lst, pthread_t *phils, int context)
{
	free(phils);
	destroy_mutex(lst->law);
	forks_clear(lst, context);
	return (err);
}
