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
	pthread_mutex_t fork;
	pthread_mutex_t eat;

}			t_mutex;

typedef struct philosopher
{
	int nb;
	long tid;
	t_mutex *mx;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int must_eat;
	long begin_time;
	long time;
	struct timeval current_time;
	long t_ms;
}			t_philo;

int	ft_atoi(const char *str);