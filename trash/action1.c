#include <philo.h>

// void	ft_wanna_eat(t_philo **philos, int i)
// {
// 	int		baglh;
// 	int 	bagrh;

// 	bagrh = i + 1;
// 	baglh = i - 1;
// 	//(i == 0) ? baglh = 13 : (void)i;
// 	if (i == 0)
// 		baglh = 13;
// 	//printf("Z%d %d %dN\n", baglh, i, bagrh);
// 	(void)philos;
	
// 	if ((*philos)[i].rh == 0 && (*philos)[i].lh == 0)
// 	{
// 		if (pthread_mutex_trylock(&(*philos)[baglh].baguette) == 0)
// 		{
// 			(*philos)[i].lh = 1;
// 			(*philos)[baglh].who = i;
// 			(*philos)[i].status = (*philos)[i].rh + (*philos)[i].lh;
// 			if (pthread_mutex_trylock(&(*philos)[bagrh].baguette) == 0)
// 			{
// 				(*philos)[i].rh = 1;
// 				(*philos)[bagrh].who = i;
// 				(*philos)[i].status = (*philos)[i].rh + (*philos)[i].lh;
// 			}
// 		} 

// 	}
// 	else if ((*philos)[i].rh == 0 && (*philos)[i].lh == 1)
// 	{
// 		if (pthread_mutex_trylock(&(*philos)[bagrh].baguette) == 0)
// 		{
// 			(*philos)[i].rh = 1;
// 			(*philos)[bagrh].who = i;
// 			(*philos)[i].status = (*philos)[i].rh + (*philos)[i].lh;

// 		}
// 	}
// 	else if ((*philos)[i].rh == 1 && (*philos)[i].lh == 0)
// 	{
// 		if (pthread_mutex_trylock(&(*philos)[baglh].baguette) == 0)
// 		{
// 			(*philos)[i].lh = 1;
// 			(*philos)[baglh].who = i;
// 			(*philos)[i].status = (*philos)[i].rh + (*philos)[i].lh;
// 		}
// 	}

// 	usleep(SEC);
// }



//////////////////////// Fonctionne en partie, add/remove des baguettes.
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

	// printf("*%d %d %d\n*", baglh, i, bagrh);

////////////////////////////////////////// Right Hand
	if ((*philos)[i].rh == 0)
	{
		if (pthread_mutex_trylock(&(*philos)[bagrh].baguette) == 0)
		{
			if (pthread_mutex_lock(&(*philos)[0].aff))
				exit(7);
			(*philos)[i].rh = 1;
			(*philos)[bagrh].who = i;
			(*philos)[i].status = (*philos)[i].rh + (*philos)[i].lh;
			if (pthread_mutex_unlock(&(*philos)[0].aff))
				exit(7);
		}
		else if ( (*philos)[r_p].status == THINK && (*philos)[r_p].lh == 1)
		{
			if (pthread_mutex_lock(&(*philos)[0].aff))
				exit(7);
			pthread_mutex_unlock(&(*philos)[bagrh].baguette);
			pthread_mutex_lock(&(*philos)[bagrh].baguette);
			(*philos)[bagrh].who = i;
			(*philos)[r_p].lh = 0;
			//(*philos)[r_p].status = (*philos)[r_p].rh + (*philos)[r_p].lh;
			(*philos)[i].rh = 1;
			(*philos)[i].status = (*philos)[i].rh + (*philos)[i].lh;
			if (pthread_mutex_unlock(&(*philos)[0].aff))
				exit(7);
			// ft_putstr_color("!!!\n", RED);
		}
	}

////////////////////////////////////////// Left Hand
	if ((*philos)[i].lh == 0 )
	{
		if (pthread_mutex_trylock(&(*philos)[baglh].baguette) == 0)
		{
			if (pthread_mutex_lock(&(*philos)[0].aff))
				exit(7);
			(*philos)[i].lh = 1;
			(*philos)[baglh].who = i;
			(*philos)[i].status = (*philos)[i].rh + (*philos)[i].lh;
			if (pthread_mutex_unlock(&(*philos)[0].aff))
				exit(7);
		}
		else if ( (*philos)[l_p].status == THINK && (*philos)[l_p].rh == 1)
		{
			if (pthread_mutex_lock(&(*philos)[0].aff))
				exit(7);
			pthread_mutex_unlock(&(*philos)[baglh].baguette);
			pthread_mutex_lock(&(*philos)[baglh].baguette);
			(*philos)[baglh].who = i;
			(*philos)[l_p].rh = 0;
			//(*philos)[l_p].status = (*philos)[l_p].lh + (*philos)[l_p].rh;
			(*philos)[i].lh = 1;
			(*philos)[i].status = (*philos)[i].rh + (*philos)[i].lh;
			if (pthread_mutex_unlock(&(*philos)[0].aff))
				exit(7);
			// ft_putstr_color("!!!\n", RED);
		}
	}

	////////////////////////////////////////// SLEEP TIMERS
	if ((*philos)[i].status == 0)
	{
		usleep(REST_T * SEC);
	}
	else if ((*philos)[i].status == 1)
	{
		usleep(THINK_T * SEC);
		if ((*philos)[i].rh == 1)
		{
			if (pthread_mutex_lock(&(*philos)[0].aff))
				exit(7);
			(*philos)[bagrh].who = -1;
			(*philos)[i].rh = 0;
			pthread_mutex_unlock(&(*philos)[bagrh].baguette);
			if (pthread_mutex_unlock(&(*philos)[0].aff))
				exit(7);
		}
		else if ((*philos)[i].lh == 1)
		{
			if (pthread_mutex_lock(&(*philos)[0].aff))
				exit(7);
			(*philos)[baglh].who = -1;
			(*philos)[i].lh = 0;
			pthread_mutex_unlock(&(*philos)[baglh].baguette);
			if (pthread_mutex_unlock(&(*philos)[0].aff))
				exit(7);
		}
		(*philos)[i].status = (*philos)[i].rh + (*philos)[i].lh;
	}
	else if ((*philos)[i].status == 2)
	{
		usleep(EAT_T * SEC);
		if (pthread_mutex_lock(&(*philos)[0].aff))
			exit(7);
		(*philos)[i].hp = MAX_LIFE;
		pthread_mutex_unlock(&(*philos)[bagrh].baguette);
		(*philos)[bagrh].who = -1;
		(*philos)[i].rh = 0;
		pthread_mutex_unlock(&(*philos)[baglh].baguette);
		(*philos)[baglh].who = -1;
		(*philos)[i].lh = 0;
		(*philos)[i].status = (*philos)[i].rh + (*philos)[i].lh;
		if (pthread_mutex_unlock(&(*philos)[0].aff))
			exit(7);
		usleep(REST_T * SEC);
	}
	////////////////////////////////////////// END
}
