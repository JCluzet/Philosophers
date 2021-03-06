/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 01:24:26 by jcluzet           #+#    #+#             */
/*   Updated: 2021/10/28 03:11:18 by jcluzet          ###   ########.fr       */
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

long int	actual_time(void)
{
	struct timeval		current_time;

	if (gettimeofday(&current_time, NULL) == -1)
		showerror("gettimeofday error\n");
	return (current_time.tv_usec);
}

void	*life(void *life)
{
	t_philo		*ph;
	t_argv		*argv;
	int			i;

	i = 0;
	ph = (t_philo *)life;
	argv = ph->p_arg;
	if (ph->nb % 2 == 0)
		usleep(1500);
	pthread_mutex_lock(&(argv->eating));
	while (!(argv->is_dead) && !(argv->all_ate))
	{
		pthread_mutex_unlock(&(argv->eating));
		eating(ph);
		pthread_mutex_lock(&(argv->eating));
		print_action(argv, ph->nb, "is sleeping");
		pthread_mutex_unlock(&(argv->eating));
		sleep_time(argv->time_ts, argv);
		pthread_mutex_lock(&(argv->eating));
		print_action(argv, ph->nb, "is thinking");
		i++;
	}
	pthread_mutex_unlock(&(argv->eating));
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
		pthread_mutex_lock(&(arg->eating));
		ph[i].last_eat = stock_time();
		pthread_mutex_unlock(&(arg->eating));
		i++;
	}
	is_dead(arg, ph);
	exit_launcher(arg);
}
