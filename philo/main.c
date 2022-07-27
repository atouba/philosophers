/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atouba <atouba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 16:29:21 by atouba            #+#    #+#             */
/*   Updated: 2022/07/27 18:27:40 by atouba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	check_death(t_philo *phs)
{
	int	i;
	int	n;

	n = phs->shared_data->n_philos;
	while (1)
	{
		i = 0;
		while (i < n)
		{
			if (!eigen_philo_death(&phs[i]))
				return ;
			i++;
		}
		// usleep(120);
	}
}

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
		i+=2;
	}
	i = 1;
	while (i < n)
	{
		pthread_create(&t[i], NULL, (void *)live, (void *)&philos[i]);
		usleep(50);
		i+=2;
	}
	while (is_philos_dead(philos))
		usleep(100);
	// check_death(philos);
}

int	main(int ac, char **av)
{
	t_shared_data	shared;
	t_philo			*philos;
	pthread_mutex_t	*mtxs;
	pthread_t		*t;

	check_args(ac, av);
	t = malloc(sizeof(pthread_t) * ft_atoi(av[1]));
	philos = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	mtxs = malloc(sizeof(pthread_mutex_t) * (ft_atoi(av[1]) + 2));
	if (!philos || !mtxs)
		return (1);	
	init_set_args(philos, av, mtxs, &shared);
	/* test */
	// printf("%d ", philos[0].shared_data.n_philos);
	all_point_to(philos, &shared, mtxs);
	launch_threads(t, philos);
}