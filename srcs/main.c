/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 01:24:26 by jcluzet           #+#    #+#             */
/*   Updated: 2021/10/27 02:35:51 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../inc/philo.h"

int	main(int argc, char **argv)
{
	t_argv	arg;

	checkargs(argc, argv);
	stockargs(argc, argv, &arg);
	starter(&arg);
	return (0);
}

void	checkdeath(t_argv *arg, t_philo *ph, int i)
{
	while (++i < arg->nb_philo && !(arg->is_dead))
	{
		pthread_mutex_lock(&(arg->eating));
		if ((stock_time() - ph[i].last_eat) > arg->time_td)
			print_action(arg, i + 1, "\033[0;31mis dead...\033[m");
		pthread_mutex_lock(&(arg->dead_check));
		if ((stock_time() - ph[i].last_eat) > arg->time_td)
			arg->is_dead = 1;
		pthread_mutex_unlock(&(arg->dead_check));
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
		checkdeath(arg, ph, i);
		pthread_mutex_lock(&(arg->dead_check));
		if (arg->is_dead)
			break ;
		i = 0;
		while (arg->time_de != -1 && i < arg->nb_philo
			&& ph[i].nb_ate >= arg->time_de)
			i++;
		pthread_mutex_unlock(&(arg->dead_check));
		if (i == arg->nb_philo)
		{
			pthread_mutex_lock(&(arg->ate));
			arg->all_ate = 1;
			pthread_mutex_unlock(&(arg->ate));
		}
	}
}

void	*life(void *life)
{
	t_philo		*ph;
	t_argv		*argv;

	ph = (t_philo *)life;
	argv = ph->p_arg;
	if (ph->nb % 2 == 0)
		usleep(1500);
	pthread_mutex_lock(&(argv->dead_check));
	while (!(argv->is_dead))
	{
		pthread_mutex_unlock(&(argv->dead_check));
		eating(ph);
		pthread_mutex_lock(&(argv->ate));
		if (argv->all_ate)
			break ;
		pthread_mutex_unlock(&(argv->ate));
		print_action(argv, ph->nb, "is sleeping");
		sleep_time(argv->time_ts, argv);
		print_action(argv, ph->nb, "is thinking");
		pthread_mutex_lock(&(argv->dead_check));
	}
	pthread_mutex_unlock(&(argv->dead_check));
	return (NULL);
}

void	starter(t_argv *arg)
{
	int		i;
	t_philo	*ph;

	i = 0;
	ph = arg->philosophers;
	arg->first_time = stock_time();
	while (i < arg->nb_philo)
	{
		if (pthread_create(&(ph[i].thread_nb), NULL, life, &(ph[i])))
			showerror("Unable to create a thread");
		pthread_mutex_lock(&(arg->last_eat));
		ph[i].last_eat = stock_time();
		pthread_mutex_unlock(&(arg->last_eat));
		i++;
	}
	is_dead(arg, ph);
	exit_launcher(arg);
}
