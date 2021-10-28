/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 03:11:40 by jcluzet           #+#    #+#             */
/*   Updated: 2021/10/28 03:12:49 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	check_eat_death(int i, t_argv *arg, t_philo *ph)
{
	while (++i < arg->nb_philo && !(arg->is_dead))
	{
		pthread_mutex_lock(&(arg->eating));
		if ((stock_time() - ph[i].last_eat) > arg->time_td)
			print_action(arg, i + 1, "\033[0;31mis dead...\033[m");
		if ((stock_time() - ph[i].last_eat) > arg->time_td)
			arg->is_dead = 1;
		pthread_mutex_unlock(&(arg->eating));
		usleep(100);
	}
}

void	is_dead(t_argv *arg, t_philo *ph)
{
	int	i;

	while (!(arg->all_ate))
	{
		i = -1;
		check_eat_death(i, arg, ph);
		if (arg->is_dead)
			break ;
		i = 0;
		pthread_mutex_lock(&(arg->eating));
		while (arg->time_de != -1 && i < arg->nb_philo
			&& ph[i].nb_ate >= arg->time_de)
			i++;
		if (i == arg->nb_philo)
			arg->all_ate = 1;
		pthread_mutex_unlock(&(arg->eating));
	}
}
