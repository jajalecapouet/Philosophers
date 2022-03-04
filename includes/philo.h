/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 10:39:09 by njaros            #+#    #+#             */
/*   Updated: 2022/03/04 16:57:50 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <pthread.h>

typedef struct fromage
{
	pthread_t		**adr;
	int				value;
	pthread_mutex_t	mut;
}	fromage;

typedef struct law
{
	int	philo_number;
	int	time_to_die;
	int	time_to_sleep;
	int	eat_number;
	int	all_alive;
}	law;

typedef struct fork_lst
{
	int				nb;
	int				enable;
	struct fork_lst	*next;
	pthread_mutex_t	mutex;
	struct law		*law;
}	fork_lst;

// Fonctions de gestion d'erreur et nettoyage

int			error(int err);
void		forks_clear(fork_lst *lst);
int			freeteuse(int err, fork_lst *lst, pthread_t *phils);

// Fonction de parsing

int			parsing_fill(char **to_parse, law *to_fill);

// Corps du programme

int			philo(law law);
void		*philo_handler(void *arg);

// Fonctions pratiques

fork_lst	*new_fork(int i);
void		lst_forkadd_back(fork_lst **lst, fork_lst *new);
int			afficher_temps_ms(struct timeval t1, struct timeval t2);
int			afficher_temps_us(struct timeval t1, struct timeval t2);

#endif
