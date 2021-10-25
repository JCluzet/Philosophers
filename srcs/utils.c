/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 16:30:11 by jcluzet           #+#    #+#             */
/*   Updated: 2021/10/25 03:32:19 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_atoi(char *str)
{
	int	num;
	int	i;

	i = 0;
	num = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - 48);
		i++;
	}
	return (num);
}

int	checksyntax(int argc, char **argv)
{
	int	i;
	int	u;

	u = 0;
	i = 1;
	while (i < argc)
	{
		while (argv[i][u])
		{
			if (argv[i][u] < '0' || argv[i][u] > '9')
				return (-1);
			u++;
		}
		u = 0;
		i++;
	}
	return (0);
}

void	print_action(t_argv *arg, int nb, char *msg)
{
	pthread_mutex_lock(&(arg->writing));
	if (!(arg->is_dead))
	{
		printf("﹝ \033[0;31m");
		printf("%4lli \033[m", stock_time() - arg->first_timestamp);
		printf("﹞ ");
		printf("\033[0;32m%i\033[m", nb);
		printf("  ➣ %s\n", msg);
	}
	pthread_mutex_unlock(&(arg->writing));
}

long long	stock_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}
