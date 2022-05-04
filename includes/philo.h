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

// Mes petits maquerots

# define CYAN "\033[01;34m"
# define ROUGE "\033[00;31m"
# define BLEU "\033[00;34m"
# define SOULIGNE "\033[04m"
# define N "\033[00m"
# define start_ok 2
# define OK 3
# define all_ready 4
# define count_done 1
# define i_died 2
# define i_rdy 3

//Mes petits bâtiments

typedef struct s_time
{
	struct timeval start;
	struct timeval current;
	struct timeval last_eat;
}	t_time;

typedef struct law
{
	int				philo_number;
	int				time_to_die;
	int				time_to_sleep;
	int				time_to_eat;
	int				eat_number;
	int				all_alive;
	int				ready_count;
	struct timeval	start;
	pthread_mutex_t	write;
	pthread_mutex_t	mutex_law;
}	law;

typedef struct fork_lst
{
	int				nb;
	int				enable;
	int				ttd;
	int				tts;
	int				tte;
	int				usleep_val;
	int				eat_n;
	int				count_eat;
	struct fork_lst	*next;
	pthread_mutex_t	mutex;
	struct law		*law;
}	fork_lst;

// Fonctions de gestion d'erreur et nettoyage.

int			error(int err);
void		forks_clear(fork_lst *lst, int context);
int			freeteuse(int err, fork_lst *lst, pthread_t *phils, int context);

// Fonction de parsing, construction de structures
// et allocation de mémoires.

fork_lst	*new_fork(int i, law *law);
void		lst_forkadd_back(fork_lst **lst, fork_lst *new);
int			parsing_fill(char **to_parse, law *to_fill);
int			insert_mutex_law(fork_lst *lst, law *law);
int			crea_forks_phils(fork_lst **forks, pthread_t **phils, int nb, law *law);

// Corps du programme.

int			philo(law law);
void		*philo_handler(void *arg);
int			je_mange(fork_lst *fourchette1, fork_lst *fourchette2, t_time *tps);
int			j_ai_fini(fork_lst *fourchette1, fork_lst *fourchette2, t_time *tps);
void		je_dors(fork_lst *fork, t_time *tps);
int			je_pense(int philo, t_time *tps, int think, law *law);

// Fonctions pratiques. 
//-> time_utils
int			ms(struct timeval t1, struct timeval t2);
int			us(struct timeval t1, struct timeval t2);
void		init_time(t_time *tps, struct timeval start);
int			keskifou(t_time *tps, int philo, char *str, law *law);
void		usleep_tricks(fork_lst *fork, int time);
//-> mutex_utils
int			val_read_law(law *law, int to_read);
void		val_write_law(fork_lst *fork, int to_write, t_time *tps);
void		val_write_fork(fork_lst *fork, int etat, int *dispo, t_time *tps);
void		val_write_fork_next(fork_lst *fork, int *token, t_time *tps);

#endif
