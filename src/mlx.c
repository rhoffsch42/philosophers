/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/12 13:35:54 by rhoffsch          #+#    #+#             */
/*   Updated: 2019/10/01 12:46:38 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void		ft_print_msg(t_env *e, int i)
{
	if (i == DANCE)
	{
		mlx_string_put(e->mlx->mlx, e->mlx->win, 165, 230, 0xFF0000, \
			"Now, it is time...");
		mlx_string_put(e->mlx->mlx, e->mlx->win, 150, 257, 0xFF0000, \
			"To DAAAAAAAANCE ! ! !");
	}
	else if (i == DEAD)
	{
		mlx_string_put(e->mlx->mlx, e->mlx->win, 170, 250, 0xFF0000, \
			"Somebody died ! ! !");
	}
}

int				ft_expose_hook(t_env *e)
{
	static int	i = 0;
	static int	x = 0;

	usleep(SEC);
	if (x != -1)
	{
		ft_print(e->philos);
		i = ft_print_mlx(e);
	}
	if ((i == DANCE || i == DEAD) && x != -1)
	{
		x = -2;
		while (x < 12)
			pthread_detach(e->philos[(x += 2)].philo) == 0 ? (void)x : exit(7);
		x = -1;
		i == DEAD ? mlx_put_image_to_window(e->mlx->mlx, e->mlx->win, \
			e->mlx->img, 0, 0) : (void)i;
		i == DEAD ? ft_print(e->philos) : (void)i;
		i == DEAD ? ft_putstr_color("Somebody died ! ! !\n", RED) : (void)i;
	}
	if (x != -1)
		mlx_put_image_to_window(e->mlx->mlx, e->mlx->win, e->mlx->img, 0, 0);
	if (i == DANCE || i == DEAD)
		ft_print_msg(e, i);
	return (0);
}

int				ft_key_hook(int keycode, t_env *e)
{
	if (keycode == 53)
		exit(0);
	mlx_destroy_image(e->mlx->mlx, e->mlx->img);
	e->mlx->img = mlx_new_image(e->mlx->mlx, e->mlx->win_x, e->mlx->win_y);
	ft_draw_bg(e->mlx, 0, 0);
	ft_expose_hook(e);
	return (0);
}

int				ft_print_stats(t_env *e, int i)
{
	int		hp;

	hp = (int)((float)((e->philos)[i].hp) \
		/ (float)((float)MAX_LIFE / (float)16));
	(((e->philos)[i].hp) <= 0) ? (e->philos)[i].status = DEAD : (void)hp;
	if (hp < 0)
		hp = 0;
	ft_mlx_imgcpy(e->mlx->xpm[(e->philos)[i].status], e->mlx->img, \
		ft_pos(i, 0), ft_pos(i, 1));
	if (hp != 0)
	{
		ft_mlx_imgcpy2(e->mlx->xhp[hp], e->mlx->img, \
			ft_pos(i, 0) - 17, ft_pos(i, 1) - 20);
	}
	return (e->philos[i].status);
}

int				ft_no_key(t_env *e)
{
	mlx_destroy_image(e->mlx->mlx, e->mlx->img);
	e->mlx->img = mlx_new_image(e->mlx->mlx, e->mlx->win_x, e->mlx->win_y);
	ft_draw_bg(e->mlx, 0, 0);
	ft_expose_hook(e);
	return (0);
}
