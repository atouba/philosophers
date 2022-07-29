/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atouba <atouba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 00:19:44 by atouba            #+#    #+#             */
/*   Updated: 2022/07/29 17:22:21 by atouba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	eat(t_philo *ph)
{
	// printf("b");
	int	i;
	int	n;
	int lock1;
	int lock2;
	
	i = 0;
	n = ph->shared_data->n_philos;
	// pthread_mutex_lock(ph->mtxs[(ph->i_philo - 1) % n]);
	// pthread_mutex_lock(ph->mtxs[ph->i_philo % n]);
	// printf("b");
	// if (sem_wait(ph->shared_data->sems) == -1 && sem_wait(ph->shared_data->sems) == -1)
	// 	printf("a");
		
	sem_wait(ph->shared_data->sems);
	sem_wait(ph->shared_data->sems);
	// lock2 = sem_wait(ph->shared_data->sems);
	// if (lock1 == -1 && lock2 == -1)
	ph->last_eat = currtime();
	// if (lock1 == -1 && lock2 == -1)
	// 	printf("lock already locked\n");
	print_partial_eat(ph);
	print_partial_eat(ph);
	print_eat(ph);
	(ph->eat_times)++;
	ph->new_st_time = currtime();
	while (time_elapsed(ph->new_st_time) < ph->shared_data->tm_eat)
		usleep(100);
	// pthread_mutex_unlock(ph->mtxs[(ph->i_philo - 1) % n]);
	// pthread_mutex_unlock(ph->mtxs[ph->i_philo % n]);
	sem_post(ph->shared_data->sems);
	sem_post(ph->shared_data->sems);
	return (1);
}

int	ft_sleep(t_philo *ph)
{
	if (ph->shared_data->dead_msg == 0)
	{
		print_sleep(ph);
	ph->new_st_time = currtime();
		while (time_elapsed(ph->new_st_time) < ph->shared_data->tm_sleep)
			usleep(100);
	}
	return (1);
}

int	think(t_philo *ph)
{
	print_think(ph);
	return (1);
}

int	check_death(t_philo *ph)
{
	// while (1)
	// {
	// 	printf("a ");
	return (0);
		if (time_elapsed(ph->last_eat) > ph->shared_data->tm_die)
		{
			print_death(ph);
			// return (1);
			exit(1);
		}
	// }
	return (0);
}

void	*live(void *p)
{
	t_philo	*ph;

	ph = (t_philo *)p;
	printf("%d\n", ph->shared_data->dead_msg);
	
	while (!check_death(ph))
	{
		eat(ph);
		ft_sleep(ph);
		think(ph);
	}
	return (0);
}
