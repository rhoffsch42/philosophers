/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/12 13:59:07 by rhoffsch          #+#    #+#             */
/*   Updated: 2019/09/26 16:38:56 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <libft.h>
# include <mlx.h>
# include <pthread.h>
# include <stdio.h>

# define MAX_LIFE	5
# define EAT_T		1
# define REST_T		1
# define THINK_T	1
# define TIMEOUT	60

# define EAT		2
# define THINK		1
# define REST		0
# define DEAD		4
# define SEC		1000000

# define NB_XPM		5

# define OK				0
# define CREATE_FAIL	1
# define JOIN_FAIL		2
# define LOCK_FAIL		3
# define UNLOCK_FAIL	4
# define TRYLOCK_FAIL	5

# define DANCE			6
# define RGB(r, g, b)(65536 * (int)(r) + 256 * (int)(g) + (int)(b))
# define SL	sizeline

typedef pthread_mutex_t	t_mutex;

typedef struct	s_im
{
	int		bpp;
	int		sizeline;
	int		endian;
	char	*px;
}				t_im;

typedef struct	s_mlx
{
	void	*mlx;
	void	*win;
	int		win_x;
	int		win_y;
	void	*img;
	void	*xpm[NB_XPM];
	void	*xhp[17];

}				t_mlx;

typedef struct	s_philo
{
	pthread_t	philo;
	int			hp;
	int			status;
	int			timeout;
	t_mutex		aff;
	t_mutex		baguette;

}				t_philo;

typedef struct	s_env
{
	t_mlx		*mlx;
	t_philo		*philos;
}				t_env;

typedef struct	s_arg
{
	int			ind;
	t_philo		**philos;
}				t_arg;

void			*philo(void *arg);
void			ft_wanna_eat(t_philo **philos, int i);
void			ft_launch_mlx(t_mlx *mlx, char *cwd);
int				ft_key_hook(int keycode, t_env *e);
int				ft_expose_hook(t_env *e);
int				ft_no_key(t_env *e);
int				ft_print_mlx(t_env *e);
int				ft_print_stats(t_env *e, int i);
int				ft_pos(int i, int dir);
void			ft_mlx_imgcpy(void *src, void *dst, int posx, int posy);
void			ft_mlx_imgcpy2(void *src, void *dst, int posx, int posy);
void			ft_draw_bg(t_mlx *mlx, int x, int y);

void			ft_print(t_philo **philos);
void			ft_introduce(t_philo philo, int i);

#endif
