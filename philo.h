/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 00:58:28 by mel-gand          #+#    #+#             */
/*   Updated: 2023/04/14 02:09:31 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<sys/time.h>

typedef struct mutex
{
	int counter;
	int dead;
	long long begin_time;
	pthread_mutex_t var;
}			t_mutex;

typedef struct s_philosopher
{
	int time;
	int nb;
	int tid;
	t_mutex *mx;
	pthread_t th;
	pthread_mutex_t *m;
	pthread_mutex_t mtx;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int meals_nb;
	int woke_up;
}			t_philo;

int	ft_atoi(const char *str);
long gettime();
void	ft_usleep(int time);