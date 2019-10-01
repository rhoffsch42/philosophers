/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/12 13:35:26 by rhoffsch          #+#    #+#             */
/*   Updated: 2019/10/01 13:16:35 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static int	get(int side, int index)
{
	if (side == LEFT)
	{
		if (index == 0)
			return (12);
		else
			return (index - 2);
	}
	else
	{
		if (index == 12)
			return (0);
		else
			return (index + 2);
	}
}

static int	*lock_baguette(t_philo *philos, int i, int baglh, int bagrh)
{
	int		*ret;

	ret = malloc(sizeof(int) * 2);
	if (!ret)
	{
		ft_putstr("Malloc failed\n");
		exit(1);
	}
	if (philos[i].timeout > philos[get(LEFT, i)].timeout)
		ret[0] = pthread_mutex_trylock(&philos[baglh].baguette);
	else
		ret[0] = pthread_mutex_lock(&philos[baglh].baguette);
	if (philos[i].timeout > philos[get(RIGHT, i)].timeout)
		ret[1] = pthread_mutex_trylock(&philos[bagrh].baguette);
	else
		ret[1] = pthread_mutex_lock(&philos[bagrh].baguette);
	return (ret);
}

static void	steal_baguette(t_philo *philos, int i, int baglh, int bagrh)
{
	int		*ret;

	if (philos[1].hp++ >= PHILOS_N && philos[i].hp > HP_LOW)
		return ;
	ret = lock_baguette(philos, i, baglh, bagrh);
	if (ret[0] == SUCCESS && ret[1] == SUCCESS)
		philos[i].status = EAT;
	else if (ret[0] == SUCCESS)
	{
		pthread_mutex_unlock(&philos[baglh].baguette);
		philos[i].status = THINK;
	}
	else if (ret[1] == SUCCESS)
	{
		pthread_mutex_unlock(&philos[bagrh].baguette);
		philos[i].status = THINK;
	}
	else
	{
		philos[i].status = THINK;
		usleep(SEC * THINK_T);
	}
	free(ret);
}

void		ft_wanna_eat(t_philo *philos, int i)
{
	int		bag_lr[2];

	bag_lr[0] = i - 1;
	bag_lr[1] = i + 1;
	(i == 0) ? bag_lr[0] = 13 : (void)i;
	if (philos[i].status == EAT)
	{
		philos[i].hp = MAX_LIFE;
		usleep(SEC * EAT_T);
		pthread_mutex_unlock(&philos[bag_lr[1]].baguette);
		pthread_mutex_unlock(&philos[bag_lr[0]].baguette);
		pthread_mutex_lock(&(philos[0].aff));
		philos[i].status = REST;
		pthread_mutex_unlock(&(philos[0].aff));
	}
	else
	{
		if (philos[i].status == REST)
			usleep(SEC * REST_T);
		steal_baguette(philos, i, bag_lr[0], bag_lr[1]);
	}
	philos[i].timeout++;
}
