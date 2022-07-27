/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atouba <atouba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 18:54:33 by atouba            #+#    #+#             */
/*   Updated: 2022/07/26 21:24:26 by atouba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	print_death(t_philo *ph)
{
	pthread_mutex_lock(&ph->mtxs[ph->shared_data->n_philos]);
	ph->shared_data->dead_msg = 1;
	printf("\033[0;31m%d %d died\033[0m\n",
		time_elapsed(ph->shared_data->start_time), ph->i_philo);
	pthread_mutex_unlock(&ph->mtxs[ph->shared_data->n_philos]);
}

int	eigen_philo_death(t_philo *ph)
{
	int	n;

	n = ph->shared_data->n_philos + 1;
	pthread_mutex_lock(&ph->mtxs[n]);
	if (time_elapsed(ph->last_eat) > ph->shared_data->tm_die)
	{
		ph->shared_data->dead_msg = 1;
		print_death(ph);
		pthread_mutex_unlock(&ph->mtxs[n]);
		for (int i = 0; i < n + 1; i++)
			pthread_mutex_destroy(&ph->mtxs[i]);
		exit (1);
	}
	pthread_mutex_unlock(&ph->mtxs[n]);
	return (0);
}