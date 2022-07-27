/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   establish.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atouba <atouba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 16:33:21 by atouba            #+#    #+#             */
/*   Updated: 2022/07/27 23:30:25 by atouba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	init_set_args(t_philo *phs, char **av, pthread_mutex_t *mtxs
					, t_shared_data *shared)
{
	int	i;

	i = 0;
	shared->n_philos = ft_atoi(av[1]);
	while (i < shared->n_philos)
	{
		phs[i].i_philo = i + 1;
		phs[i].new_st_time = currtime();
		phs[i].eat_times = 0;
		phs[i].last_eat = currtime();
		pthread_mutex_init(&mtxs[i], 0);
		i++;
	}
	pthread_mutex_init(&mtxs[i], 0);
	pthread_mutex_init(&mtxs[i + 1], 0);
	shared->tm_die = ft_atoi(av[2]);
	shared->tm_eat = ft_atoi(av[3]);
	shared->tm_sleep = ft_atoi(av[4]);
	shared->start_time = currtime();
	shared->dead_msg = 0;
	shared->total_must_eat = -1;
	if (av[5])
		shared->total_must_eat = ft_atoi(av[5]);
}

int	is_not_num(char c)
{
	if (c < '0' || c > '9')
		return (1);
	return (0);
}

int	check_args(int ac, char **av)
{
	int	i;
	int	j;
	int	n;

	i = 1;
	if (ac > 6 || ac < 5)
		return (0);
	if (ft_atoi(av[1]) == 0)
		return (0);
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (is_not_num(av[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	if (ft_atoi(av[1]) == 1)
		printf("\033[0;32m0 1 has taken a fork\033[0m\n");
	return (1);
}

void	all_point_to(t_philo *philos, t_shared_data *shared
					, pthread_mutex_t *mtxs)
{
	int	i;
	int	n;

	i = 0;
	n = shared->n_philos;
	while (i < n)
	{
		philos[i].shared_data = shared;
		philos[i].mtxs = mtxs;
		i++;
	}
}
