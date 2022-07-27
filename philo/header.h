/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atouba <atouba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 16:18:50 by atouba            #+#    #+#             */
/*   Updated: 2022/07/26 18:59:58 by atouba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
#define HEADER_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef	struct shared_data
{
	int				n_philos;
	int				tm_eat;
	int				tm_sleep;
	int				tm_die;
	int				total_must_eat;
	long long		start_time;
	int				dead_msg;
}	t_shared_data;

typedef struct s_philo
{
	int				i_philo;
	long long		new_st_time;  // maybe one global value in the struct above would do the job
	int				eat_times;
	int				last_eat;
	pthread_mutex_t	*mtxs;
	pthread_mutex_t	*dead_mtx;
	t_shared_data	*shared_data;
}	t_philo;

int				ft_atoi(const char *str);
int				check_args(int ac, char **av);
int				allocate_to_nums(t_philo *phs);
void			init_set_args(t_philo *phs, char **av, pthread_mutex_t *mtxs, t_shared_data *shared);
void			all_point_to(t_philo *philos, t_shared_data *shared, pthread_mutex_t *mtxs);
long long		currtime(void);
int				time_elapsed(long long start_time);
int				print_partial_eat(t_philo *ph);
int				print_eat(t_philo *ph);
int				print_sleep(t_philo *ph);
int				print_think(t_philo *ph);
void			print_death(t_philo *ph);
void			*live(void *p);
int				eigen_philo_death(t_philo *ph);

#endif