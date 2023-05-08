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
}			t_mutex;


/*
	int nb;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int meals_nb;
	t_args
*/
typedef struct s_philosopher
{
	int Zzz;
	int nb;
	int tid;
	int begin_time;
	t_mutex *mx;
	pthread_mutex_t *m;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int meals_nb;
	int dead;
	//t_args	*args;
}			t_philo;

int	ft_atoi(const char *str);