/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atouba <atouba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 16:29:21 by atouba            #+#    #+#             */
/*   Updated: 2022/07/31 17:40:49 by atouba           ###   ########.fr       */
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

void	*check_death(void *p)
{
	t_philo	*ph;

	ph = p;
	while (1)
	{
		if (time_elapsed(ph->last_eat) > ph->shared_data->tm_die)
			break ;
		usleep(50);
	}
	print_death(ph);
	exit(1);
	return (0);
}

void	init(t_philo *philos, int n, t_shared_data *shared)
{
	int	i;

	i = 0;
	while (i < n)
	{
		philos[i].shared_data = shared;
		philos[i].new_st_time = currtime();
		philos[i].eat_times = 0;
		philos[i].last_eat = currtime();
		philos[i].shared_data = shared;
		philos[i].i_philo = i + 1;
		i++;
	}
}

void	launch_processes(pthread_t *t, t_philo *philos, t_shared_data *shared
		, pthread_t *thread_death)
{
	int	i;
	int	n;
	int	pid[200];

	i = -1;
	n = shared->n_philos;
	shared->sems = sem_open("sems", O_CREAT, 777, n);
	shared->print_sem = sem_open("print_sem", O_CREAT, 777, 1);
	while (++i < n)
	{
		init(philos, n, shared);
		pid[i] = fork();
		if (pid[i] == 0)
		{
			pthread_create(&t[i], 0, check_death, (void *)&philos[i]);
			live(&philos[i]);
		}
	}
	i = -1;
	waitpid(-1, 0, 0);
	while (++i < n)
		kill(pid[i], SIGKILL);
	exit(1);
}

int	main(int ac, char **av)
{
	t_shared_data	shared;
	t_philo			*philos;
	pthread_t		*t;
	pthread_t		*thread_death;

	if (!check_args(ac, av))
		return (0);
	t = malloc(sizeof(pthread_t) * ft_atoi(av[1]));
	thread_death = malloc(sizeof(pthread_t));
	philos = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	init_set_args(philos, av, &shared);
	all_point_to(philos, &shared);
	launch_processes(t, philos, &shared, thread_death);
}
