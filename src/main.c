/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/12 13:35:36 by rhoffsch          #+#    #+#             */
/*   Updated: 2019/09/26 17:41:51 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	ft_launch_philo(t_philo **philos)
{
	t_arg	*arg;
	int		i;

	arg = (t_arg*)malloc(sizeof(t_arg) * 14);
	(*philos)[0].aff = (t_mutex)PTHREAD_MUTEX_INITIALIZER;
	(*philos)[0].timeout = TIMEOUT;
	i = 1;
	while (i < 14)
	{
		(*philos)[i].baguette = (t_mutex)PTHREAD_MUTEX_INITIALIZER;
		i += 2;
	}
	i = 0;
	while (i < 14)
	{
		(*philos)[i].hp = MAX_LIFE;
		(*philos)[i].status = REST;
		arg[i].philos = philos;
		arg[i].ind = i;
		if (pthread_create(&((*philos)[i].philo), NULL, philo, \
			(void*)&(arg[i])))
			exit(CREATE_FAIL);
		i = i + 2;
	}
}

void	ft_print(t_philo **philos)
{
	int		i;

	i = 0;
	if (pthread_mutex_lock(&(*philos)[0].aff))
		exit(7);
	while (i < 14)
	{
		ft_introduce((*philos)[i], i);
		i += 2;
	}
	if (pthread_mutex_unlock(&(*philos)[0].aff))
		exit(7);
	ft_putchar(10);
}

int		ft_pos(int i, int dir)
{
	int		pos[7][2];

	pos[0][0] = 220;
	pos[0][1] = 30;
	pos[1][0] = 370;
	pos[1][1] = 90;
	pos[2][0] = 430;
	pos[2][1] = 250;
	pos[3][0] = 320;
	pos[3][1] = 400;
	pos[4][0] = 140;
	pos[4][1] = 405;
	pos[5][0] = 25;
	pos[5][1] = 260;
	pos[6][0] = 70;
	pos[6][1] = 100;
	return (pos[i / 2][dir]);
}

int		ft_print_mlx(t_env *e)
{
	int		i;
	int		x;

	x = 0;
	pthread_mutex_lock(&(e->philos)[0].aff) == 0 ? (void)x : exit(7);
	if (((e->philos)[0].timeout)-- == 0)
	{
		ft_putstr_color("Now, it is time... To DAAAAAAAANCE ! ! !\n", CYAN);
		pthread_mutex_unlock(&(e->philos)[0].aff) == 0 ? (void)x : exit(7);
		return (DANCE);
	}
	i = 0;
	while (i < 14)
	{
		if ((e->philos)[i].status != EAT)
			(e->philos)[i].hp--;
		else
			(e->philos)[i].hp = MAX_LIFE;
		x = (ft_print_stats(e, i) == DEAD) ? DEAD : x;
		i += 2;
	}
	pthread_mutex_unlock(&(e->philos)[0].aff) == 0 ? (void)x : exit(7);
	return (x);
}

int		main(int ac, char **av)
{
	t_env		*e;
	int			i;

	(void)ac;
	if (!(e = (t_env*)malloc(sizeof(t_env))) || \
		!(e->mlx = (t_mlx*)malloc(sizeof(t_mlx))) || \
		!(e->philos = (t_philo*)malloc(sizeof(t_philo) * 14)))
		ft_putendl("Error: malloc failed");
	ft_launch_philo(&(e->philos));
	ft_launch_mlx(e->mlx, av[0]);
	mlx_key_hook(e->mlx->win, ft_key_hook, e);
	mlx_expose_hook(e->mlx->win, ft_expose_hook, e);
	mlx_loop_hook(e->mlx->mlx, ft_no_key, e);
	mlx_loop(e->mlx->mlx);
	i = 0;
	while (i < 14)
	{
		if (pthread_join(e->philos[i].philo, NULL) != 0)
			exit(JOIN_FAIL);
		i = i + 2;
	}
	return (0);
}
