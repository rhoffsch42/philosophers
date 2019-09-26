/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/12 13:36:10 by rhoffsch          #+#    #+#             */
/*   Updated: 2015/10/12 13:36:12 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*philo(void *arg)
{
	t_arg	*args;

	args = (t_arg*)arg;
	while (1)
		ft_wanna_eat(args->philos, args->ind);
	pthread_exit(NULL);
}

void	ft_pv(int hp)
{
	int		i;

	i = 0;
	ft_putchar('[');
	COLOR(GREEN);
	while (i < 16)
	{
		ft_putchar((i < hp) ? '=' : ' ');
		i++;
	}
	COLOR(NOCOLOR);
	ft_putchar(']');
}

void	ft_introduce(t_philo philo, int i)
{
	int		hp;

	ft_putchar('(');
	ft_putnbr((i / 2) + 1);
	ft_putstr(") ");
	hp = (int)((float)philo.hp / (float)((float)MAX_LIFE / (float)16));
	ft_pv(hp);
	ft_putchar(' ');
	ft_putnbr(philo.hp);
	ft_putchar('\t');
	if (philo.status == REST)
		ft_putstr("REST");
	if (philo.status == THINK)
		ft_putstr("THINK");
	if (philo.status == EAT)
		ft_putstr("EAT");
	ft_putchar('\n');
}
