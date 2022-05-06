/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <njaros@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 10:39:09 by njaros            #+#    #+#             */
/*   Updated: 2022/05/06 09:39:16 by njaros           ###   ########lyon.fr   */
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
# define START_OK 2
# define OK 3
# define ALL_READY 4
# define COUNT_DONE 1
# define I_DIED 2
# define I_RDY 3

//Mes petits bâtiments

typedef struct s_time
{
	struct timeval	start;
	struct timeval	current;
	struct timeval	last_eat;
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
}	t_law;

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
	t_law			*law;
}	t_fork_lst;

// Fonctions de gestion d'erreur et nettoyage.

int			error(int err);
void		forks_clear(t_fork_lst *lst, int context);
int			freeteuse(int err, t_fork_lst *lst, pthread_t *phils, int context);

// Fonction de parsing, construction de structures
// et allocation de mémoires.

t_fork_lst	*new_fork(int i, t_law *law);
void		lst_forkadd_back(t_fork_lst **lst, t_fork_lst *new);
int			parsing_fill(char **to_parse, t_law *to_fill);
int			insert_mutex_law(t_fork_lst *lst, t_law *law);
int			c(t_fork_lst **forks, pthread_t **phils, int nb, t_law *law);

// Corps du programme.

int			philo(t_law law, int nb_philo);
void		*philo_handler(void *arg);
int			je_mange(t_fork_lst *f1, t_fork_lst *f2, t_time *tps);
int			j_ai_fini(t_fork_lst *f1, t_fork_lst *f2, t_time *tps);
void		je_dors(t_fork_lst *fork, t_time *tps);
int			je_pense(int philo, t_time *tps, int think, t_law *law);

// Fonctions pratiques. 
//-> time_utils
int			ms(struct timeval t1, struct timeval t2);
int			us(struct timeval t1, struct timeval t2);
void		init_time(t_time *tps, struct timeval start);
int			keskifou(t_time *tps, int philo, char *str, t_law *law);
void		usleep_tricks(t_fork_lst *fork, int time);
//-> mutex_utils
int			val_read_law(t_law *law, int to_read);
void		val_write_law(t_fork_lst *fork, int to_write, t_time *tps);
void		val_write_fork(t_fork_lst *fork, int etat, int *dispo, t_time *tps);
void		val_write_fork_next(t_fork_lst *fork, int *token, t_time *tps);

#endif
