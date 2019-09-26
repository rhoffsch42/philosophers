/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/12 13:35:26 by rhoffsch          #+#    #+#             */
/*   Updated: 2015/10/12 13:35:29 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static	void	ft_more_baguette(t_philo **philos, int i, int baglh, int bagrh)
{
	if (pthread_mutex_trylock(&(*philos)[baglh].baguette) == 0)
	{
		if (pthread_mutex_trylock(&(*philos)[bagrh].baguette) == 0)
		{
			pthread_mutex_lock(&(*philos)[0].aff);
			(*philos)[i].status = EAT;
			pthread_mutex_unlock(&(*philos)[0].aff);
		}
		else
		{
			pthread_mutex_unlock(&(*philos)[baglh].baguette);
			pthread_mutex_lock(&(*philos)[0].aff);
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

void			ft_wanna_eat(t_philo **philos, int i)
{
	int		baglh;
	int		bagrh;

	bagrh = i + 1;
	baglh = i - 1;
	(i == 0) ? baglh = 13 : (void)i;
	if ((*philos)[i].status == EAT)
	{
		usleep(1 * SEC * EAT_T);
		pthread_mutex_unlock(&(*philos)[bagrh].baguette);
		pthread_mutex_unlock(&(*philos)[baglh].baguette);
		pthread_mutex_lock(&(*philos)[0].aff);
		(*philos)[i].status = REST;
		pthread_mutex_unlock(&(*philos)[0].aff);
	}
	else if ((*philos)[i].status == THINK)
		ft_more_baguette(philos, i, baglh, bagrh);
	else if ((*philos)[i].status == REST)
	{
		usleep(1 * SEC * REST_T);
		pthread_mutex_lock(&(*philos)[0].aff);
		(*philos)[i].status = THINK;
		pthread_mutex_unlock(&(*philos)[0].aff);
	}
}
