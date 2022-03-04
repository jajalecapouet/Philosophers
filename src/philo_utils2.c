/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 15:22:52 by njaros            #+#    #+#             */
/*   Updated: 2022/03/04 15:44:11 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

fork_lst	*new_fork(int i)
{
	fork_lst	*new;

	new = malloc(sizeof(fork_lst));
	if (!new)
		return (NULL);
	new->nb = i;
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
	}
}
