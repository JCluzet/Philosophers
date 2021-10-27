/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 15:32:41 by jcluzet           #+#    #+#             */
/*   Updated: 2021/10/27 02:34:43 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

struct			s_argv;

typedef struct s_philo
{
	pthread_t		thread_nb;
	int				nb;
	int				nb_ate;
	int				l_fork;
	int				r_fork;
	long long		last_eat;
	struct s_argv	*p_arg;
}			t_philo;

typedef struct s_argv
{
	pthread_mutex_t	eating;
	pthread_mutex_t	forks[250];
	pthread_mutex_t	writing;
	pthread_mutex_t	dead_check;
	pthread_mutex_t	last_eat;
	pthread_mutex_t	ate;
	long long		first_time;
	int				is_dead;
	int				nb_philo;
	int				all_ate;
	int				time_de;
	long int		time_td;
	long int		time_te;
	long int		time_ts;
	t_philo			philosophers[250];
}			t_argv;

void		checkargs(int argc, char **argv);
void		showerror(char *str);
int			ft_strlen(char *str);
int			init_mutex(t_argv *arg);
void		starter(t_argv *arg);
int			init(t_argv *argv);
void		checkdeath(t_argv *arg, t_philo *ph, int i);
void		eating(t_philo *philo);
void		exit_launcher(t_argv *arg);
long long	stock_time(void);
void		*life(void *life);
void		is_dead(t_argv *arg, t_philo *ph);
void		sleep_time(long long time, t_argv *arg);
void		print_action(t_argv *arg, int nb, char *msg);
int			ft_atoi(char *str);
int			checksyntax(int argc, char **argv);
void		stockargs(int argc, char **argv, t_argv *arg);

#endif 
