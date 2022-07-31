/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atouba <atouba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 00:19:44 by atouba            #+#    #+#             */
/*   Updated: 2022/07/31 00:18:49by atouba           ###   ########.fr       */
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
	// if (sem_wait(ph->sem) == -1 && sem_wait(ph->sem) == -1)
	// 	printf("error in sem wait\n");
	sem_wait(ph->shared_data->sems);
	sem_wait(ph->shared_data->sems);

	// sem_wait(ph->sem_eats);
	
	// printf("b");
	// printf("n : %d\n", n);
	int s = 0;
	int a = 3;
	// while (s == 0)
	// {
	// 	s = sem_wait(ph->shared_data->sems);
	// 	printf("%d\n", a);
	// 	a++;
	// }
	// printf("before sem_wait\n");
	print_partial_eat(ph);
	ph->last_eat = currtime();
	print_partial_eat(ph);
	print_eat(ph);
	(ph->eat_times)++;
	// printf("philo %d eat times: %d\n", ph->i_philo, ph->eat_times);
	ph->new_st_time = currtime();
	while (time_elapsed(ph->new_st_time) < ph->shared_data->tm_eat)
	{
		// printf("uSleeping");
		usleep(100);
	}
	// pthread_mutex_unlock(ph->mtxs[(ph->i_philo - 1) % n]);
	// pthread_mutex_unlock(ph->mtxs[ph->i_philo % n]);
	sem_post(ph->shared_data->sems);
	sem_post(ph->shared_data->sems);
	// if (sem_post(ph->sem) == -1 && sem_post(ph->sem) == -1)
	// 	printf("error in sem post\n");
	return (1);
}

int	ft_sleep(t_philo *ph)
{
	// if (ph->shared_data->dead_msg == 0)
	// {
		print_sleep(ph);
	ph->new_st_time = currtime();
		while (time_elapsed(ph->new_st_time) < ph->shared_data->tm_sleep)
			usleep(100);
	// }
	return (1);
}

int	think(t_philo *ph)
{
	print_think(ph);
	return (1);
}

// int	check_death(t_philo *ph)
// {
// 	// while (1)
// 	// {
// 	// 	printf("a ");
// 	return (0);
// 		if (time_elapsed(ph->last_eat) > ph->shared_data->tm_die)
// 		{
// 			print_death(ph);
// 			// return (1);
// 			exit(1);
// 		}
// 	// }
// 	return (0);
// }

void	*live(void *p)
{
	t_philo	*ph;
	static int	i;
	ph = (t_philo *)p;
	// printf("%d\n", ph->shared_data->dead_msg);

	while (!ph->shared_data->dead_msg)
	{
	// printf("Hello\n");
	// printf("%d        ", ph->shared_data->dead_msg);
		eat(ph);
		ft_sleep(ph);
		think(ph);
		if (ph->eat_times == ph->shared_data->total_must_eat)
			exit(1);
	}
	exit(1);
	return (0);
}
