/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_msgs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atouba <atouba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 02:33:50 by atouba            #+#    #+#             */
/*   Updated: 2022/07/26 15:48:52by atouba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	print_partial_eat(t_philo *ph)
{
		pthread_mutex_lock(&ph->mtxs[ph->shared_data->n_philos]);
	if (!ph->shared_data->dead_msg)
	{
		printf("\033[0;32m%d %d has taken a fork dead_msg: %d\033[0m\n",
			time_elapsed(ph->shared_data->start_time), ph->i_philo, ph->shared_data->dead_msg);
		pthread_mutex_unlock(&ph->mtxs[ph->shared_data->n_philos]);
		return (1);
	}
	return (0);
}

int	print_eat(t_philo *ph)
{
		pthread_mutex_lock(&ph->mtxs[ph->shared_data->n_philos]);
	if (!ph->shared_data->dead_msg)
	{
		printf("\033[0;32m%d %d is eating dead_msg: %d\033[0m\n",
			time_elapsed(ph->shared_data->start_time), ph->i_philo, ph->shared_data->dead_msg);
		pthread_mutex_unlock(&ph->mtxs[ph->shared_data->n_philos]);
		return (1);
	}
	return (0);
}

int	print_sleep(t_philo *ph)
{
	pthread_mutex_lock(&ph->mtxs[ph->shared_data->n_philos]);
	if (!ph->shared_data->dead_msg)
	{
		printf("\033[0;35m%d %d is sleeping dead_msg: %d\033[0m\n",
			time_elapsed(ph->shared_data->start_time), ph->i_philo, ph->shared_data->dead_msg);
		pthread_mutex_unlock(&ph->mtxs[ph->shared_data->n_philos]);
		return (1);
	}
	return (0);
}

int	print_think(t_philo *ph)
{
		pthread_mutex_lock(&ph->mtxs[ph->shared_data->n_philos]);
	if (!ph->shared_data->dead_msg)
	{
		printf("\033[0;36m%d %d is thinking dead_msg: %d\033[0m\n",
			time_elapsed(ph->shared_data->start_time), ph->i_philo, ph->shared_data->dead_msg);
		pthread_mutex_unlock(&ph->mtxs[ph->shared_data->n_philos]);
		return (1);
	}
	return (0);
}
