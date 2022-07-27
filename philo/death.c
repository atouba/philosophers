/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atouba <atouba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 18:54:33 by atouba            #+#    #+#             */
/*   Updated: 2022/07/27 20:06:13 by atouba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	min(t_philo *phs)
{
	int	i;
	int	n;
	int	min;

	i = 1;
	n = phs->shared_data->n_philos;
	min = phs[0].eat_times;
	while (i < n)
	{
		if (phs[i].eat_times < min)
			min = phs[i].eat_times;
		i++;
	}
	return (min);
}

void	print_death(t_philo *ph)
{
	pthread_mutex_lock(&ph->mtxs[ph->shared_data->n_philos]);
	ph->shared_data->dead_msg = 1;
	printf("\033[0;31m%d %d died\033[0m\n",
		time_elapsed(ph->shared_data->start_time), ph->i_philo);
	pthread_mutex_unlock(&ph->mtxs[ph->shared_data->n_philos]);
}
