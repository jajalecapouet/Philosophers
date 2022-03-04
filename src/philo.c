/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 11:01:30 by njaros            #+#    #+#             */
/*   Updated: 2022/03/04 16:31:36 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error(int err)
{
	if (err == 0)
	{
		write(1, "Bon déroulement du processus\n", 31);
		write(1, "En esperant qu'il n'y a pas eu trop de mort...\n", 48);
	}
	if (err == 1)
		write(2, "Opération non autorisée\n", 27);
	if (err == 5)
		write(2, "Erreur d'E/S\n", 13);
	if (err == 11)
		write(2, "Erreur mémoire\n", 16);
	if (err == 22)
		write(2, "Argument(s) non valide\n", 24);
	return (err);
}

int	main(int ac, char **av)
{
	struct law	law;
	int			err;

	err = 0;
	if (ac != 5)
		return (error(5));
	err = parsing_fill(av, &law);
	if (err)
		return (error(err));
	return (philo(law));
}

int	philo(law law)
{
	int			i;
	int			secure;
	pthread_t	*phils;
	fork_lst	*forks;

	secure = crea_forks_phils(&forks, &phils, law.philo_number, &law);
	if (secure)
		return (freeteuse(secure, forks, phils));
	i = -1;
	while (++i < law.philo_number)
	{
		secure = pthread_create(&phils[i], NULL, philo_handler, forks);
		if (secure)
		{
			while (--i >= 0)
				pthread_detach(phils[i]);
			return (secure);
		}
		forks = forks->next;
	}
	while (--i >= 0)
		pthread_join(phils[i], NULL);
	return (0);
}