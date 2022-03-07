/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 10:39:09 by njaros            #+#    #+#             */
/*   Updated: 2022/03/07 17:45:22 by njaros           ###   ########lyon.fr   */
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

# define BLEUCLAIR "\033[01;34m"
# define ROUGE "\033[00;31m"
# define BLEU "\033[00;34m"
# define SOULIGNE "\033[04m"
# define NORMAL "\033[00m"

// Si j'ai oublié d'enlever la structure fromage,
// elle ne me servait que pour un programme test
// pour m'initier aux pthreads et ses fonctions.

typedef struct fromage
{
	pthread_t		**adr;
	int				value;
	pthread_mutex_t	mut;
}	fromage;

typedef struct s_time
{
	struct timeval start;
	struct timeval current;
	struct timeval last_eat;
}	t_time;

typedef struct law
{
	int	philo_number;
	int	time_to_die;
	int	time_to_sleep;
	int	time_to_eat;
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

// Fonctions de gestion d'erreur et nettoyage.

int			error(int err);
void		forks_clear(fork_lst *lst);
int			freeteuse(int err, fork_lst *lst, pthread_t *phils);

// Fonction de parsing, construction de structures
// et allocation de mémoires.

int			parsing_fill(char **to_parse, law *to_fill);
int			insert_mutex_law(fork_lst *lst, law *law);
int			crea_forks_phils(fork_lst **forks, pthread_t **phils, int nb, law *law);

// Corps du programme.

int			philo(law law);
int			keskifou(t_time *tps, int philo, char *str);
void		*philo_handler(void *arg);
int			je_mange(fork_lst *fourchette1, fork_lst *fourchette2, t_time *tps);
int			j_ai_fini(fork_lst *fourchette1, fork_lst *fourchette2);
void		je_dors(fork_lst *fork, t_time *tps);
int			je_pense(int philo, t_time *tps, int think);

// Fonctions pratiques.

fork_lst	*new_fork(int i);
void		lst_forkadd_back(fork_lst **lst, fork_lst *new);
int			ms(struct timeval t1, struct timeval t2);
int			us(struct timeval t1, struct timeval t2);
void		init_time(t_time *tps);

#endif
