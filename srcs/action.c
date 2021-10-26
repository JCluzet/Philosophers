/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 01:24:26 by jcluzet           #+#    #+#             */
/*   Updated: 2021/10/26 17:44:36 by jcluzet          ###   ########.fr       */
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
	pthread_mutex_lock(&(arg->last_eat));
	philo->last_eat = stock_time();
	pthread_mutex_unlock(&(arg->last_eat));
	pthread_mutex_unlock(&(arg->eating));
	sleep_time(arg->time_te, arg);
	pthread_mutex_lock(&(arg->eating));
	(philo->nb_ate)++; // lui ?
	pthread_mutex_unlock(&(arg->eating));
	pthread_mutex_unlock(&(arg->forks[philo->l_fork]));
	pthread_mutex_unlock(&(arg->forks[philo->r_fork]));
}

void	sleep_time(long long time, t_argv *arg)
{
	long long	i;

	i = stock_time();
	pthread_mutex_lock(&(arg->eating)); // rajout ? 
	while (!(arg->is_dead)) // pose blem
	{
		pthread_mutex_unlock(&(arg->eating)); // rajout ?
		if ((stock_time() - i) >= time)
			break ;
		usleep(50);
		pthread_mutex_lock(&(arg->eating)); // rajout ?
	}
	pthread_mutex_unlock(&(arg->eating)); // rajout ?
}
