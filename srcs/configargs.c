/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configargs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 16:22:36 by jcluzet           #+#    #+#             */
/*   Updated: 2021/10/25 15:01:24 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	checkargs(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		showerror("./philo need at least 5 args and 6 max.");
	if (checksyntax(argc, argv) == -1)
		showerror("Please enter only digits in arguments");
	if (ft_atoi(argv[1]) == 0 || ft_atoi(argv[2]) == 0
		|| ft_atoi(argv[3]) == 0 || ft_atoi(argv[4]) == 0)
		showerror("A argument must be positive");
}

void	stockargs(int argc, char **argv, t_argv *arg)
{
	arg->nb_philo = ft_atoi(argv[1]);
	arg->time_td = ft_atoi(argv[2]);
	arg->time_te = ft_atoi(argv[3]);
	arg->time_ts = ft_atoi(argv[4]);
	if (argc == 6)
		arg->time_de = ft_atoi(argv[5]);
	else
		arg->time_de = -1;
	if (init(arg) == 1)
		showerror("Initialisation fail");
}
