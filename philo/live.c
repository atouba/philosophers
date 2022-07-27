/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atouba <atouba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 00:19:44 by atouba            #+#    #+#             */
/*   Updated: 2022/07/27 20:17:04 by atouba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	eat(t_philo *ph)
{
	int	i;
	int	n;

	i = 0;
	n = ph->shared_data->n_philos;
	pthread_mutex_lock(&ph->mtxs[(ph->i_philo - 1) % n]);
	pthread_mutex_lock(&ph->mtxs[ph->i_philo % n]);
	ph->last_eat = currtime();
	print_partial_eat(ph);
	print_partial_eat(ph);
	print_eat(ph);
	(ph->eat_times)++;
	ph->new_st_time = currtime();
	while (time_elapsed(ph->new_st_time) < ph->shared_data->tm_eat)
		usleep(100);
	pthread_mutex_unlock(&ph->mtxs[(ph->i_philo - 1) % n]);
	pthread_mutex_unlock(&ph->mtxs[ph->i_philo % n]);
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

void	*live(void *p)
{
	t_philo	*ph;

	ph = (t_philo *)p;
	while (!ph->shared_data->dead_msg)
	{
		eat(ph);
		ft_sleep(ph);
		think(ph);
	}
	return (0);
}
