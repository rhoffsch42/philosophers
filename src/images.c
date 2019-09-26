/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/12 13:35:45 by rhoffsch          #+#    #+#             */
/*   Updated: 2019/09/26 17:42:43 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void		check_ptr(void *ptr, char *msg)
{
	if (!ptr)
	{
		ft_putstr("Error : ");
		ft_putendl(msg);
		exit(20);
	}
}

static char		**build_paths(char *cwd)
{
	int			i;
	char		*prefix;
	char		**paths;
	static char	*p[22] = {"img/sleeps.XPM", "img/thinks.XPM", "img/eats.XPM",
"img/tables.XPM", "img/deads.XPM", "img/1.XPM", "img/1.XPM", "img/2.XPM",
"img/3.XPM", "img/4.XPM", "img/5.XPM", "img/6.XPM", "img/7.XPM",
"img/8.XPM", "img/9.XPM", "img/10.XPM", "img/11.XPM", "img/12.XPM",
"img/13.XPM", "img/14.XPM", "img/15.XPM", "img/16.XPM"};

	prefix = ft_strrchr(cwd, '/');
	prefix[1] = 0;
	paths = (char**)malloc(sizeof(char*) * 23);
	check_ptr(paths, "Error: malloc failed");
	i = 0;
	while (i < 22)
	{
		paths[i] = ft_strjoin(cwd, p[i]);
		i++;
	}
	paths[i] = NULL;
	return (paths);
}

void			ft_get_img(t_mlx *mlx, char *cwd)
{
	int			w;
	int			h;
	int			i;
	char		**paths;

	paths = build_paths(cwd);
	i = 0;
	while (i < 5)
	{
		mlx->xpm[i] = mlx_xpm_file_to_image(mlx->mlx, paths[i], &w, &h);
		check_ptr(mlx->xpm[i], "mlx_xpm_file_to_image failed");
		free(paths[i]);
		i++;
	}
	i = 0;
	while (i < 17)
	{
		mlx->xhp[i] = mlx_xpm_file_to_image(mlx->mlx, paths[i + 5], &w, &h);
		check_ptr(mlx->xhp[i], "mlx_xpm_file_to_image failed");
		free(paths[i + 5]);
		i++;
	}
	free(paths);
}

void			ft_draw_bg(t_mlx *mlx, int x, int y)
{
	t_im	im1;
	t_im	im2;
	int		tmp1;
	int		tmp2;

	im1.px = mlx_get_data_addr(mlx->xpm[3], &im1.bpp, &im1.SL, &im1.endian);
	im2.px = mlx_get_data_addr(mlx->img, &im2.bpp, &im2.SL, &im2.endian);
	while (x < mlx->win_x)
	{
		y = 0;
		while (y < mlx->win_y)
		{
			tmp1 = y * im1.SL + (im1.bpp / 8) * x;
			tmp2 = y * im2.SL + (im2.bpp / 8) * x;
			im2.px[tmp2] = im1.px[tmp1];
			im2.px[tmp2 + 1] = im1.px[tmp1 + 1];
			im2.px[tmp2 + 2] = im1.px[tmp1 + 2];
			y++;
		}
		x++;
	}
}

void			ft_launch_mlx(t_mlx *mlx, char *cwd)
{
	if ((mlx->mlx = mlx_init()) == NULL)
	{
		ft_putstr_color("mlx_init failed\n", RED);
		exit(1);
	}
	ft_get_img(mlx, cwd);
	mlx->win_x = 500;
	mlx->win_y = 500;
	mlx->img = mlx_new_image(mlx->mlx, mlx->win_x, mlx->win_y);
	ft_draw_bg(mlx, 0, 0);
	mlx->win = mlx_new_window(mlx->mlx, mlx->win_x, mlx->win_y, "philo");
}
