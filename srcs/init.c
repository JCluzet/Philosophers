/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 23:20:43 by jcluzet           #+#    #+#             */
/*   Updated: 2021/10/27 02:29:31 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	init_mutex(t_argv *arg)
{
	if (pthread_mutex_init(&(arg->writing), NULL))
		return (1);
	if (pthread_mutex_init(&(arg->eating), NULL))
		return (1);
	if (pthread_mutex_init(&(arg->dead_check), NULL))
		return (1);
	if (pthread_mutex_init(&(arg->last_eat), NULL))
		return (1);
	if (pthread_mutex_init(&(arg->ate), NULL))
		return (1);
	return (0);
}

int	init(t_argv *arg)
{
	int	i;

	i = arg->nb_philo;
	arg->is_dead = 0;
	arg->all_ate = 0;
	if (arg->nb_philo > 250)
		showerror("You can't use more than 250 philosophers");
	if (init_mutex(arg) == 1)
		return (1);
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(arg->forks[i]), NULL))
			return (1);
		arg->philosophers[i].nb = i + 1;
		arg->philosophers[i].nb_ate = 0;
		arg->philosophers[i].l_fork = i;
		arg->philosophers[i].r_fork = (i + 1) % arg->nb_philo;
		arg->philosophers[i].last_eat = 0;
		arg->philosophers[i].p_arg = arg;
	}
	return (0);
}

void	showerror(char *str)
{
	write(1, "\033[31mError\033[00m\n", 17);
	write (1, str, ft_strlen(str));
	write(1, "\n", 1);
	exit(0);
}

void	exit_launcher(t_argv *arg)
{
	t_philo	*ph;
	int		i;

	ph = arg->philosophers;
	i = 0;
	while (i < arg->nb_philo)
	{
		pthread_join(ph[i].thread_nb, NULL);
		i++;
	}
	i = arg->nb_philo + 1;
	while (--i >= 0)
	{
		pthread_mutex_destroy(&(arg->forks[i]));
	}
	pthread_mutex_destroy(&(arg->writing));
	pthread_mutex_destroy(&(arg->eating));
	pthread_mutex_destroy(&(arg->dead_check));
	pthread_mutex_destroy(&(arg->last_eat));
	pthread_mutex_destroy(&(arg->ate));
}
