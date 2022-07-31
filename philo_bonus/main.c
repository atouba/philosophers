/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atouba <atouba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 16:29:21 by atouba            #+#    #+#             */
/*   Updated: 2022/07/29 17:23:37by atouba           ###   ########.fr       */
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

// int	check_death(t_philo *ph)
// {
// 	while (1)
// 	{
// 		printf("a ");
// 		if (time_elapsed(ph->last_eat) > ph->shared_data->tm_die)
// 		{
// 			print_death(ph);
// 			return (1);
// 		}
// 	}
// 	return (0);
// }

void	*check_death(void *p)
{
	t_philo *ph = p;

	while (1)
	{
		if (time_elapsed(ph->last_eat) > ph->shared_data->tm_die)
			break ;
		usleep(50);
	}
	// if (ph->shared_data->is_all_eat == 1)
	// 	exit(1);
	print_death(ph);
	exit(1);
	return (0);
}

void	*is_all_eat(void *p)
{
	int		i;
	int		n;
	t_philo	*phs;
	int		min;

	phs = (t_philo *)p;
	n = phs[0].shared_data->n_philos;
	while (min < phs[0].shared_data->total_must_eat)
	{
		i = 0;
		while (i < n)
		{
			if (phs[i].eat_times < min)
				min = phs[i].eat_times;
			i++;
		}
		// printf("total_must_eat: %d\n", phs[i].shared_data->total_must_eat);
		// printf("min_of_eats: %d\n", min);
		// printf("eat_times: %d\n", phs[i].eat_times);
		// fflush(stdout);
		usleep(100);
	}
	phs->shared_data->is_all_eat = 1;
	// exit(0);
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
		philos[i].last_eat = currtime();// pid[i] = fork();
		philos[i].shared_data = shared;
		philos[i].i_philo = i + 1;
		i++;
	}
}

void	launch_processes(pthread_t *t, t_philo *philos, t_shared_data *shared, pthread_t *thread_death)
{
	int	i;
	int	n;
	int	pid[200];
	int	k;

	i = 0;
	n = shared->n_philos;
	shared->sems = sem_open("sems", O_CREAT, 777, n);
	if (shared->total_must_eat != -1)
	{
		shared->sem_eats = sem_open("sem_eats", O_CREAT, 777, n * shared->total_must_eat);
	}
	shared->print_sem = sem_open("print_sem", O_CREAT, 777, 1);
	while (i < n)
	{
		// philos[i].shared_data = shared;
		// philos[i].new_st_time = currtime();
		// philos[i].eat_times = 0;
		// philos[i].last_eat = currtime();// pid[i] = fork();
		// philos[i].shared_data = shared;
		// philos[i].i_philo = i + 1;
		init(philos, n, shared);
		pid[i] = fork();
		if (pid[i] == 0)
		{
			pthread_create(&t[i], 0, check_death, (void *)&philos[i]);
			live(&philos[i]);
		}
		else
			i++;
		k = 0;
	}
	i = -1;
	waitpid(-1, 0, 0);
	for (int j = 0; j < n; j++)
		kill(pid[j], SIGKILL);
	exit(1);
}

int	main(int ac, char **av)
{
	t_shared_data	shared;
	t_philo			*philos;
	// pthread_mutex_t	*mtxs;
	pthread_t		*t;
	pthread_t		*thread_death;
	// sem_t			sems = 0;
	// sem_t			print_sem = 0;

	if (!check_args(ac, av))
		return (0);
	t = malloc(sizeof(pthread_t) * ft_atoi(av[1]));
	thread_death = malloc(sizeof(pthread_t));
	philos = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	init_set_args(philos, av, &shared);
	all_point_to(philos, &shared);
	launch_processes(t, philos, &shared, thread_death);
}
