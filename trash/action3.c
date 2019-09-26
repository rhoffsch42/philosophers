#include <philo.h>

void	ft_wanna_eat(t_philo **philos, int i)
{
	int		baglh;
	int 	bagrh;

	bagrh = i + 1;
	baglh = i - 1;
	(i == 0) ? baglh = 13 : (void)i;


	if ((*philos)[i].status == EAT)
	{
		usleep(1 * SEC * EAT_T);
		pthread_mutex_unlock(&(*philos)[bagrh].baguette);
		pthread_mutex_unlock(&(*philos)[baglh].baguette);
		pthread_mutex_lock(&(*philos)[0].aff);
		(*philos)[i].lh = 0;
		(*philos)[i].rh = 0;
		(*philos)[bagrh].who = -1;
		(*philos)[baglh].who = -1;
		(*philos)[i].status = REST;
		pthread_mutex_unlock(&(*philos)[0].aff);
	}
	else if ((*philos)[i].status == THINK)
	{
		if (pthread_mutex_trylock(&(*philos)[baglh].baguette) == 0)
		{
			if (pthread_mutex_trylock(&(*philos)[bagrh].baguette) == 0)
			{
				pthread_mutex_lock(&(*philos)[0].aff);
				(*philos)[(*philos)[baglh].who].rh = 0;
				(*philos)[(*philos)[bagrh].who].lh = 0;
				(*philos)[i].lh = 1;
				(*philos)[i].rh = 1;
				(*philos)[bagrh].who = i;
				(*philos)[baglh].who = i;
				(*philos)[i].status = EAT;
				pthread_mutex_unlock(&(*philos)[0].aff);
			}
			else
			{
				pthread_mutex_unlock(&(*philos)[baglh].baguette);
				pthread_mutex_lock(&(*philos)[0].aff);
				(*philos)[i].lh = 1;
				(*philos)[(*philos)[baglh].who].rh = 0;
				(*philos)[baglh].who = i;
				(*philos)[i].status = THINK;
				pthread_mutex_unlock(&(*philos)[0].aff);
			}
		}
		else if (pthread_mutex_trylock(&(*philos)[bagrh].baguette) == 0)
		{
			if (pthread_mutex_trylock(&(*philos)[baglh].baguette) == 0)
			{
				pthread_mutex_lock(&(*philos)[0].aff);
				(*philos)[(*philos)[baglh].who].rh = 0;
				(*philos)[(*philos)[bagrh].who].lh = 0;
				(*philos)[i].lh = 1;
				(*philos)[i].rh = 1;
				(*philos)[bagrh].who = i;
				(*philos)[baglh].who = i;
				(*philos)[i].status = EAT;
				pthread_mutex_unlock(&(*philos)[0].aff);
			}
			else
			{
				pthread_mutex_unlock(&(*philos)[bagrh].baguette);
				pthread_mutex_lock(&(*philos)[0].aff);
				(*philos)[i].rh = 1;
				(*philos)[(*philos)[bagrh].who].lh = 0;
				(*philos)[bagrh].who = i;
				(*philos)[i].status = THINK;
				pthread_mutex_unlock(&(*philos)[0].aff);
			}
		}
		else
		{
			pthread_mutex_lock(&(*philos)[0].aff);
			(*philos)[i].status = THINK;
			pthread_mutex_unlock(&(*philos)[0].aff);
			usleep(1 * SEC * THINK_T);
		}
	}
	else if ((*philos)[i].status == REST)
	{
		usleep(1 * SEC * REST_T);
		pthread_mutex_lock(&(*philos)[0].aff);
		(*philos)[i].status = THINK;
		pthread_mutex_unlock(&(*philos)[0].aff);
	}
}

// pthread_mutex_lock(&(*philos)[0].aff);
// pthread_mutex_unlock(&(*philos)[0].aff);
