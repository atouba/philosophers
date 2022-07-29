/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_msgs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atouba <atouba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 02:33:50 by atouba            #+#    #+#             */
/*   Updated: 2022/07/29 12:05:34 by atouba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	print_partial_eat(t_philo *ph)
{
	// pthread_mutex_lock(&ph->mtxs[ph->shared_data->n_philos]);
	sem_wait(ph->shared_data->print_sem);
	if (!ph->shared_data->dead_msg)
	{
		printf("\033[0;32m%d %d has taken a fork\033[0m\n",
			time_elapsed(ph->shared_data->start_time), ph->i_philo);
	sem_post(ph->shared_data->print_sem);
		// pthread_mutex_unlock(&ph->mtxs[ph->shared_data->n_philos]);
		return (1);
	}
	return (0);
}

int	print_eat(t_philo *ph)
{
	// pthread_mutex_lock(&ph->mtxs[ph->shared_data->n_philos]);
	sem_wait(ph->shared_data->print_sem);
	if (!ph->shared_data->dead_msg)
	{
		printf("\033[0;32m%d %d is eating\033[0m\n",
			time_elapsed(ph->shared_data->start_time), ph->i_philo);
		// pthread_mutex_unlock(&ph->mtxs[ph->shared_data->n_philos]);
	sem_post(ph->shared_data->print_sem);
		return (1);
	}
	return (0);
}

int	print_sleep(t_philo *ph)
{
	// pthread_mutex_lock(&ph->mtxs[ph->shared_data->n_philos]);
	sem_wait(ph->shared_data->print_sem);
	if (!ph->shared_data->dead_msg)
	{
		printf("\033[0;35m%d %d is sleeping\033[0m\n",
			time_elapsed(ph->shared_data->start_time), ph->i_philo);
		// pthread_mutex_unlock(&ph->mtxs[ph->shared_data->n_philos]);
	sem_post(ph->shared_data->print_sem);
		return (1);
	}
	return (0);
}

int	print_think(t_philo *ph)
{
	// pthread_mutex_lock(&ph->mtxs[ph->shared_data->n_philos]);
	sem_wait(ph->shared_data->print_sem);
	if (!ph->shared_data->dead_msg)
	{
		printf("\033[0;36m%d %d is thinking\033[0m\n",
			time_elapsed(ph->shared_data->start_time), ph->i_philo);
		// pthread_mutex_unlock(&ph->mtxs[ph->shared_data->n_philos]);
	sem_post(ph->shared_data->print_sem);
		return (1);
	}
	return (0);
}
