/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atouba <atouba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 00:19:44 by atouba            #+#    #+#             */
/*   Updated: 2022/07/31 17:44:48 by atouba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	eat(t_philo *ph)
{
	int	i;
	int	n;

	i = 0;
	n = ph->shared_data->n_philos;
	sem_wait(ph->shared_data->sems);
	sem_wait(ph->shared_data->sems);
	print_partial_eat(ph);
	ph->last_eat = currtime();
	print_partial_eat(ph);
	print_eat(ph);
	(ph->eat_times)++;
	ph->new_st_time = currtime();
	while (time_elapsed(ph->new_st_time) < ph->shared_data->tm_eat)
		usleep(100);
	sem_post(ph->shared_data->sems);
	sem_post(ph->shared_data->sems);
	return (1);
}

int	ft_sleep(t_philo *ph)
{
	print_sleep(ph);
	ph->new_st_time = currtime();
	while (time_elapsed(ph->new_st_time) < ph->shared_data->tm_sleep)
		usleep(100);
	return (1);
}

int	think(t_philo *ph)
{
	print_think(ph);
	return (1);
}

void	*live(void *p)
{
	t_philo	*ph;

	ph = (t_philo *)p;
	while (!ph->shared_data->dead_msg)
	{
		eat(ph);
		ft_sleep(ph);
		think(ph);
		if (ph->eat_times == ph->shared_data->total_must_eat)
			exit(1);
	}
	exit(1);
	return (0);
}
