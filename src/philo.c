/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <njaros@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 11:01:30 by njaros            #+#    #+#             */
/*   Updated: 2022/05/06 09:44:46 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error(int err)
{
	if (err == 1)
		write(2, "Opération non autorisée\n", 27);
	if (err == 3)
		write(2, "Aucun processus de ce type\n", 28);
	if (err == 5)
		write(2, "Erreur d'E/S\n", 13);
	if (err == 11 || err == 12)
		write(2, "Erreur mémoire\n", 16);
	if (err == 22)
		write(2, "Argument(s) non valide\n", 24);
	if (err == 36)
		write(2, "Un interblocage des ressources se produirait.\n", 47);
	return (err);
}

int	main(int ac, char **av)
{
	t_law	law;
	int		err;

	err = 0;
	if (ac < 5 || ac > 6)
		return (error(5));
	err = parsing_fill(&av[1], &law);
	if (err)
		return (error(err));
	if (!law.philo_number)
		return (0);
	return (error(philo(law, law.philo_number)));
}

int	philo(t_law law, int nb_philo)
{
	int				i;
	int				secure;
	pthread_t		*phils;
	t_fork_lst		*forks;

	secure = c(&forks, &phils, law.philo_number, &law);
	if (secure)
		return (freeteuse(secure, forks, phils, 0));
	i = -1;
	while (++i < nb_philo)
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
	while (--i >= 0 && !pthread_join(phils[i], NULL))
		pthread_detach(phils[i]);
	return (freeteuse(0, forks, phils, 1));
}
