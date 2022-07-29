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

int	check_pid(int pid[200], int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (pid[i] == 0)
			return (1);
		i++;
	}
	return (0);
}

void	launch_processes(pthread_t *t, t_philo *philos)
{
	int	i;
	int	n;
	int	pid[200];
	
	i = 0;
	n = philos->shared_data->n_philos;
	while (i < n)
	{
		printf("XX\n");
		// fflush(stdout);
		pid[i] = fork();
		if (pid[i] == 0)
		{
			// sleep(3);
			philos->i_philo = i + 1;
			pthread_create(&t[i], 0, live, philos);
			// while (1);
			// live(&philos[i]);
			// check_death(&philos[i]);
			// sleep(3);
			// exit(1);
		}
		i++;
	}
	i = 0;
	while (i < n)
	{
		if (pid[i] == 0)
			waitpid(pid[i], 0, 0);
		i++;
	}
	// while (1)
	// while (!check_pid(pid, n))
	// 	usleep(50);
	// i = 0;
	// while (i < n)
	// {
	// 	kill(pid[i], SIGABRT);
	// 	i++;
	// }
	// if (pid == 0)
	// {
	// 	while (is_philos_dead(philos)
	// 		&& (min(philos) < philos->shared_data->total_must_eat
	// 			|| philos->shared_data->total_must_eat == -1))
	// 	{
	// 		printf("A ");
	// 		usleep(100);
	// 	}
	// 	exit(1);
	// }
}

int	main(int ac, char **av)
{
	t_shared_data	shared;
	t_philo			philos;
	// pthread_mutex_t	*mtxs;
	pthread_t		*t;
	// sem_t			sems = 0;
	// sem_t			print_sem = 0;

	if (!check_args(ac, av))
		return (0);
	t = malloc(sizeof(pthread_t) * ft_atoi(av[1]));
	// philos = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	// if (!t || !philos || philos->shared_data->sems == SEM_FAILED || philos->shared_data->print_sem == SEM_FAILED)
	// 	return (1);
	init_set_args(&philos, av, &shared);
	all_point_to(&philos, &shared);
	launch_processes(t, &philos);
}
