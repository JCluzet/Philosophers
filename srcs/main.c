/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 01:24:26 by jcluzet           #+#    #+#             */
/*   Updated: 2021/10/25 14:00:51 by jcluzet          ###   ########.fr       */
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

void	starter(t_argv *arg)
{
	int		i;
	t_philo	*ph;

	i = 0;
	ph = arg->philosophers;
	arg->first_timestamp = stock_time();
	while (i < arg->nb_philo)
	{
		if (pthread_create(&(ph[i].thread_nb), NULL, life, &(ph[i])))
			showerror("Impossible de creer un nouveau thread");
		ph[i].last_eat = stock_time();
		i++;
	}
	is_dead(arg, ph);
	exit_launcher(arg);
}

void	is_dead(t_argv *arg, t_philo *ph)
{
	int	i;

	while (!(arg->all_ate))
	{
		i = -1;
		while (++i < arg->nb_philo && !(arg->is_dead))
		{
			pthread_mutex_lock(&(arg->eating));
			if ((stock_time() - ph[i].last_eat) > arg->time_td)
			{
				print_action(arg, i + 1, "\033[0;31mis dead...\033[m");
				arg->is_dead = 1;
			}
			pthread_mutex_unlock(&(arg->eating));
			usleep(100);
		}
		if (arg->is_dead)
			break ;
		i = 0;
		while (arg->time_de != -1 && i < arg->nb_philo
			&& ph[i].nb_ate >= arg->time_de)
			i++;
		if (i == arg->nb_philo)
			arg->all_ate = 1;
	}
}

long int	actual_time(void)
{
	long int			time;
	struct timeval		current_time;

	time = 0;
	if (gettimeofday(&current_time, NULL) == -1)
		showerror("Gettimeofday returned -1\n");
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
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
	while (!(argv->is_dead))
	{
		eating(ph);
		if (argv->all_ate)
			break ;
		print_action(argv, ph->nb, "is sleeping");
		sleep_time(argv->time_ts, argv);
		print_action(argv, ph->nb, "is thinking");
		i++;
	}
	return (NULL);
}
