/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_imgcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/12 13:36:03 by rhoffsch          #+#    #+#             */
/*   Updated: 2015/10/12 13:36:05 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int		ft_check(int xy[2], t_im im1, int *tmp1)
{
	int		color;

	*tmp1 = xy[1] * im1.SL + (im1.bpp / 8) * xy[0];
	color = RGB(im1.px[*tmp1], im1.px[*tmp1 + 1], im1.px[*tmp1 + 2]);
	if (color == -65793)
		return (0);
	return (1);
}

void	ft_mlx_imgcpy(void *src, void *dst, int posx, int posy)
{
	t_im	im1;
	t_im	im2;
	int		tmp1;
	int		tmp2;
	int		xy[2];

	xy[0] = 0;
	im1.px = mlx_get_data_addr(src, &im1.bpp, &im1.SL, &im1.endian);
	im2.px = mlx_get_data_addr(dst, &im2.bpp, &im2.SL, &im2.endian);
	while (xy[0] < 50 && (xy[0] + posx) < 500)
	{
		xy[1] = 0;
		while (xy[1] < 50 - 1)
		{
			if (ft_check(xy, im1, &tmp1) == 1 && (xy[1] + posy) < 500)
			{
				tmp2 = (xy[1] + posy) * im2.SL + (im2.bpp / 8) * (xy[0] + posx);
				im2.px[tmp2] = im1.px[tmp1];
				im2.px[tmp2 + 1] = im1.px[tmp1 + 1];
				im2.px[tmp2 + 2] = im1.px[tmp1 + 2];
			}
			(xy[1])++;
		}
		(xy[0])++;
	}
}

void	ft_mlx_imgcpy2(void *src, void *dst, int posx, int posy)
{
	t_im	im1;
	t_im	im2;
	int		tmp1;
	int		tmp2;
	int		xy[2];

	xy[0] = 0;
	im1.px = mlx_get_data_addr(src, &im1.bpp, &im1.SL, &im1.endian);
	im2.px = mlx_get_data_addr(dst, &im2.bpp, &im2.SL, &im2.endian);
	while (xy[0] < 85 && (xy[0] + posx) < 500)
	{
		xy[1] = 0;
		while (xy[1] < 85 - 1)
		{
			if (ft_check(xy, im1, &tmp1) == 1 && (xy[1] + posy) < 500)
			{
				tmp2 = (xy[1] + posy) * im2.SL + (im2.bpp / 8) * (xy[0] + posx);
				im2.px[tmp2] = im1.px[tmp1];
				im2.px[tmp2 + 1] = im1.px[tmp1 + 1];
				im2.px[tmp2 + 2] = im1.px[tmp1 + 2];
			}
			(xy[1])++;
		}
		(xy[0])++;
	}
}
