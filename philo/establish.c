/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   establish.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atouba <atouba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 16:33:21 by atouba            #+#    #+#             */
/*   Updated: 2022/07/26 14:24:07by atouba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// int	allocate_to_nums(t_philo *phs)
// {
// 	int	i;
// 	int	n;
	
// 	i = 0;
// 	n = phs->shared_data.n_philos;
// 	while (i < n)
// 	{
// 		// phs[i].i_philo = malloc(sizeof(int));     // will it be this value outside the scope of the function
// 		phs[i].i_philo = i + 1;     // will it be this value outside the scope of the function
// 		phs[i].new_st_time = malloc(sizeof(long long));    // should each philo have his own new_st_time or a global new_st_time is enough and what's exactly the diff
// 		phs[i].eat_times = malloc(sizeof(int));
// 		phs[i].last_eat = malloc(sizeof(int));
// 		i++;
// 	}
// 	phs->shared_data.dead_msg = malloc(sizeof(int));
// 	if (!phs[i].new_st_time ||   // should each philo have his own new_st_time or a global new_st_time is enough and what's exactly the diff
// 		!phs[i].eat_times ||
// 		!phs[i].last_eat)
// 		return (0);
// 	return (1);
// }

void	init_set_args(t_philo *phs, char **av, pthread_mutex_t *mtxs, t_shared_data *shared)
{
	int	i;

	// if (allocate_to_nums(phs) == 0)
	// 	return ;		// set this function accordingly
	i = 0;
	shared->n_philos = ft_atoi(av[1]);
	// printf("%d\n", shared->n_philos);
	while (i < shared->n_philos)
	{
		// *phs[i].i_philo = i + 1;
		phs[i].i_philo = i + 1;
		phs[i].new_st_time = currtime();    // should each philo have his own new_st_time or a global new_st_time is enough and what's exactly the diff
		phs[i].eat_times = 0;
		phs[i].last_eat = currtime();
		pthread_mutex_init(&mtxs[i], 0);
		i++;
	}
	pthread_mutex_init(&mtxs[i], 0);
	pthread_mutex_init(&mtxs[i + 1], 0);
	shared->tm_die = ft_atoi(av[2]);   // will it be this value outside the scope of the function
	shared->tm_eat = ft_atoi(av[3]);
	shared->tm_sleep = ft_atoi(av[4]);
	shared->start_time = currtime();
	shared->dead_msg = 0;
	if (av[5])
		shared->total_must_eat = ft_atoi(av[5]);
	else
		shared->total_must_eat = -1;
}

int	check_args(int ac, char **av)
{
	if (ac > 6 || ac < 5)
		return (0);
	if (ft_atoi(av[1]) == 0)
		return (0);
	return (1);
}

void	all_point_to(t_philo *philos, t_shared_data *shared, pthread_mutex_t *mtxs)
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