#include <philo.h>

void	ft_wanna_eat(t_philo **philos, int i)
{
	int		baglh;
	int 	bagrh;
	int 	l_p;
	int 	r_p;

	bagrh = i + 1;
	baglh = i - 1;
	r_p = i + 2;
	l_p = i - 2;
	(r_p == 14) ? r_p = 0 : (void)i;
	(l_p == -2) ? l_p = 12 : (void)i;
	(i == 0) ? baglh = 13 : (void)i;

////////////////////////////////////////// Right Hand
	if (pthread_mutex_lock(&(*philos)[bagrh].baguette))
		exit(LOCK_FAIL);
	if (pthread_mutex_lock(&(*philos)[0].aff))
		exit(LOCK_FAIL);
	if ((*philos)[r_p].status != EAT)
	{
		if ((*philos)[r_p].status == REST \
			|| (*philos)[r_p].hp > (*philos)[i].hp)
		{
			(*philos)[i].rh = 1;
			(*philos)[r_p].lh = 0;
			(*philos)[bagrh].who = i;
			(*philos)[i].status = (*philos)[i].rh + (*philos)[i].lh;
		}
	}
	if (pthread_mutex_unlock(&(*philos)[0].aff))
		exit(UNLOCK_FAIL);
	if (pthread_mutex_unlock(&(*philos)[bagrh].baguette))
		exit(UNLOCK_FAIL);
////////////////////////////////////////// Left Hand
	if (pthread_mutex_lock(&(*philos)[baglh].baguette))
		exit(LOCK_FAIL);
	if (pthread_mutex_lock(&(*philos)[0].aff))
		exit(LOCK_FAIL);
	if ((*philos)[l_p].status != EAT)
	{
		if ((*philos)[l_p].status == REST \
			|| (*philos)[l_p].hp > (*philos)[i].hp)// if();else inverse
		{
			(*philos)[i].lh = 1;
			(*philos)[l_p].rh = 0;
			(*philos)[baglh].who = i;
			(*philos)[i].status = (*philos)[i].rh + (*philos)[i].lh;
		}
	}
	if (pthread_mutex_unlock(&(*philos)[0].aff))
		exit(UNLOCK_FAIL);
	if (pthread_mutex_unlock(&(*philos)[baglh].baguette))
		exit(UNLOCK_FAIL);
////////////////////////////////////////// SLEEP TIMERS
	

	if ((*philos)[i].status == 0)
		usleep(REST_T * SEC);
	else if ((*philos)[i].status == 1)
	{
		usleep(THINK_T * SEC);
		if (pthread_mutex_lock(&(*philos)[bagrh].baguette) \
			|| pthread_mutex_lock(&(*philos)[baglh].baguette))
			exit(LOCK_FAIL);
		if ((*philos)[i].rh == 1)
		{
			if (pthread_mutex_lock(&(*philos)[0].aff))
				exit(LOCK_FAIL);
			(*philos)[bagrh].who = -1;
			(*philos)[i].rh = 0;
			(*philos)[i].status = (*philos)[i].rh + (*philos)[i].lh;
			if (pthread_mutex_unlock(&(*philos)[0].aff))
				exit(UNLOCK_FAIL);
		}
		else if ((*philos)[i].lh == 1)
		{
			if (pthread_mutex_lock(&(*philos)[0].aff))
				exit(LOCK_FAIL);
			(*philos)[baglh].who = -1;
			(*philos)[i].lh = 0;
			(*philos)[i].status = (*philos)[i].rh + (*philos)[i].lh;
			pthread_mutex_unlock(&(*philos)[baglh].baguette);
			if (pthread_mutex_unlock(&(*philos)[0].aff))
				exit(UNLOCK_FAIL);
		}
		if (pthread_mutex_unlock(&(*philos)[bagrh].baguette) \
			|| pthread_mutex_unlock(&(*philos)[baglh].baguette))
			exit(UNLOCK_FAIL);
	}
	else if ((*philos)[i].status == 2)
	{
		usleep(EAT_T * SEC);
		if (pthread_mutex_lock(&(*philos)[bagrh].baguette) \
			|| pthread_mutex_lock(&(*philos)[baglh].baguette))
			exit(LOCK_FAIL);
		if (pthread_mutex_lock(&(*philos)[0].aff))
			exit(LOCK_FAIL);
		(*philos)[i].hp = MAX_LIFE;
		(*philos)[bagrh].who = -1;
		(*philos)[i].rh = 0;
		(*philos)[baglh].who = -1;
		(*philos)[i].lh = 0;
		(*philos)[i].status = (*philos)[i].rh + (*philos)[i].lh;
		if (pthread_mutex_unlock(&(*philos)[0].aff))
			exit(UNLOCK_FAIL);
		if (pthread_mutex_unlock(&(*philos)[bagrh].baguette) \
			|| pthread_mutex_unlock(&(*philos)[baglh].baguette))
			exit(UNLOCK_FAIL);
		usleep(1 * REST_T * SEC);
	}
	////////////////////////////////////////// END
}