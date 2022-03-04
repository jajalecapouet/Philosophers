/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 15:41:44 by njaros            #+#    #+#             */
/*   Updated: 2022/03/04 15:58:38 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	forks_clear(fork_lst *lst)
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
		free(temp);
	}
}

int	freeteuse(int err, fork_lst *lst, pthread_t *phils)
{
	free(phils);
	forks_clear(lst);
	return (err);
}