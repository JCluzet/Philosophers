/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 01:24:26 by jcluzet           #+#    #+#             */
/*   Updated: 2021/10/28 02:48:13 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../inc/philo.h"

void	eating(t_philo *philo)
{
	t_argv	*arg;

	arg = philo->p_arg;
	pthread_mutex_lock(&(arg->forks[philo->l_fork]));
	print_action(arg, philo->nb, "has taken a fork");
	pthread_mutex_lock(&(arg->forks[philo->r_fork]));
	print_action(arg, philo->nb, "has taken a fork");
	pthread_mutex_lock(&(arg->eating));
	print_action(arg, philo->nb, "is eating");
	philo->last_eat = stock_time();
	pthread_mutex_unlock(&(arg->eating));
	sleep_time(arg->time_te, arg);
	(philo->nb_ate)++;
	pthread_mutex_unlock(&(arg->forks[philo->l_fork]));
	pthread_mutex_unlock(&(arg->forks[philo->r_fork]));
}

void	sleep_time(long long time, t_argv *arg)
{
	long long	i;

	i = stock_time();
	pthread_mutex_lock(&(arg->eating));
	while (!(arg->is_dead) && (!((stock_time() - i) >= time)))
	{
		pthread_mutex_unlock(&(arg->eating));
		usleep(50);
		pthread_mutex_lock(&(arg->eating));
	}
	pthread_mutex_unlock(&(arg->eating));
}
