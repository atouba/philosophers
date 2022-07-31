/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   establish.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atouba <atouba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 16:33:21 by atouba            #+#    #+#             */
/*   Updated: 2022/07/31 17:46:04 by atouba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	init_set_args(t_philo *ph, char **av
					, t_shared_data *shared)
{
	int	i;
	int	n;

	i = 0;
	shared->n_philos = ft_atoi(av[1]);
	n = shared->n_philos;
	if (sem_unlink("sems") == -1 || sem_unlink("print_sem") == -1)
		printf("error in sem_unlink\n");
	shared->tm_die = ft_atoi(av[2]);
	shared->tm_eat = ft_atoi(av[3]);
	shared->tm_sleep = ft_atoi(av[4]);
	shared->start_time = currtime();
	shared->dead_msg = 0;
	shared->total_must_eat = -1;
	shared->is_all_eat = -1;
	if (av[5])
	{
		shared->total_must_eat = ft_atoi(av[5]);
		shared->is_all_eat = 0;
	}
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

void	all_point_to(t_philo *philo, t_shared_data *shared)
{
	int	i;
	int	n;

	i = 0;
	n = shared->n_philos;
	while (i < n)
	{
		philo[i].shared_data = shared;
		i++;
	}
}
