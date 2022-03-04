#include "philo.h"

void	*pouet(void *i)
{
	
	int	a;

	pthread_mutex_lock(&(((fromage *)i)->mut));
	printf("\nsalut, je suis un thread et mon pid.pit est : %d.%d\n", getpid(), (int)pthread_self());
	a = 0;
	while (a < 100000)
	{
		(*(fromage *)i).value += 1;
		a++;
	}
	pthread_mutex_unlock(&(((fromage *)i)->mut));
	return (NULL);
}

int	main(void)
{
	struct timeval	t1;
	struct timeval	t2;
	struct fromage	camembert;
	pthread_t		*p1;
	pthread_t		*p2;
	int				pid;
	

	pthread_mutex_init(&camembert.mut, NULL);
	pid = getpid();
	printf("\nsalut, je suis main et mon pid est : %d\n", pid);
	camembert.value = 0;
	p1 = malloc(sizeof(pthread_t));
	p2 = malloc(sizeof(pthread_t));
	gettimeofday(&t1, NULL);
	camembert.adr = malloc(sizeof(pthread_t *) * 2);
	camembert.adr[0] = p1;
	camembert.adr[1] = p2;
	printf("avant le thread, i vaut %d\n", camembert.value);
	if (!pthread_create(p1, NULL, pouet, (void *) &camembert) && !pthread_create(p2, NULL, pouet, (void *) &camembert))
		printf("les thread ont fonctionné\n");
	else
		printf("CKC\n");
	pthread_join(*p1, NULL);
	pthread_join(*p2, NULL);
	pthread_detach(*p1);
	pthread_detach(*p2);
	pthread_mutex_destroy(&camembert.mut);
	free(camembert.adr[0]);
	free(camembert.adr[1]);
	free(camembert.adr);
	printf("après la fin des threads, i vaut %d\n", camembert.value);
	gettimeofday(&t2, NULL);
	afficher_temps_us(t1, t2);
	return (0);
}