/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atouba <atouba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 16:29:21 by atouba            #+#    #+#             */
/*   Updated: 2022/07/27 21:48:30 by atouba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	is_philos_dead(t_philo *phs)
{
	int	i;
	int	n;

	i = 0;
	n = phs->shared_data->n_philos;
	while (i < n)
	{
		if (time_elapsed(phs[i].last_eat) > phs->shared_data->tm_die)
		{
			print_death(&phs[i]);
			return (0);
		}
		i++;
	}
	return (1);
}

void	launch_threads(pthread_t *t, t_philo *philos)
{
	int	i;
	int	n;

	i = 0;
	n = philos->shared_data->n_philos;
	while (i < n)
	{
		pthread_create(&t[i], NULL, (void *)live, (void *)&philos[i]);
		usleep(50);
		i += 2;
	}
	i = 1;
	while (i < n)
	{
		pthread_create(&t[i], NULL, (void *)live, (void *)&philos[i]);
		usleep(50);
		i += 2;
	}
	while (is_philos_dead(philos)
		&& (min(philos) < philos->shared_data->total_must_eat
			|| philos->shared_data->total_must_eat == -1))
		usleep(100);
}

int	main(int ac, char **av)
{
	t_shared_data	shared;
	t_philo			*philos;
	pthread_mutex_t	*mtxs;
	pthread_t		*t;

	if (!check_args(ac, av))
		return (0);
	t = malloc(sizeof(pthread_t) * ft_atoi(av[1]));
	philos = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	mtxs = malloc(sizeof(pthread_mutex_t) * (ft_atoi(av[1]) + 2));
	if (!t || !philos || !mtxs)
		return (1);
	init_set_args(philos, av, mtxs, &shared);
	all_point_to(philos, &shared, mtxs);
	launch_threads(t, philos);
}
