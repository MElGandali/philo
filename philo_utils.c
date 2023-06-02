/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 23:28:38 by mel-gand          #+#    #+#             */
/*   Updated: 2023/06/02 17:49:11 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	init_var(t_philo *philo, t_mutex *mutex, char **argv)
{
	int	i;

	i = 0;
	philo->nb = ft_atoi(argv[1]);
	while (i < philo->nb)
	{
		philo[i].mx = mutex;
		i++;
	}
	philo->mx->counter = philo->nb;
	philo->mx->dead = 0;
	philo->mx->begin_time = gettime();
}

long	gettime(void)
{
	struct timeval	current_time;
	long			time;

	gettimeofday(&current_time, NULL);
	time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	return (time);
}

int	ft_usleep(t_philo *philo, int time)
{
	long	start;

	start = gettime();
	while (gettime() - start < time)
	{
		pthread_mutex_lock(&philo->mx->var);
		if (philo->mx->dead == 1)
		{
			pthread_mutex_unlock(&philo->mx->var);
			return (1);
		}
		else
			pthread_mutex_unlock(&philo->mx->var);
		usleep(60);
	}
	return (0);
}

int	supervise_meals(t_philo *philo)
{
	pthread_mutex_lock(&philo->mx->var);
	philo->meals_nb--;
	pthread_mutex_unlock(&philo->mx->var);
	if (philo->meals_nb == 0)
	{
		pthread_mutex_lock(&philo->mx->var);
		philo->mx->counter--;
		if (philo->mx->counter == 0)
		{
			pthread_mutex_unlock(&philo->mx->var);
			return (0);
		}
		pthread_mutex_unlock(&philo->mx->var);
	}
	return (1);
}

int	monitor_death(t_philo *philo, int i)
{
	pthread_mutex_unlock(&philo[i].mx->var);
	pthread_mutex_lock(&philo[i].mx->var);
	if ((gettime() - philo->mx->begin_time)
		- philo[i].woke_up >= philo[i].time_to_die)
	{
		pthread_mutex_unlock(&philo[i].mx->var);
		pthread_mutex_lock(&philo[i].mx->var);
		philo->mx->dead = 1;
		printf("%lld  %d died\n", gettime()
			- philo[i].mx->begin_time, philo[i].tid);
		pthread_mutex_unlock(&philo[i].mx->var);
		return (0);
	}
	pthread_mutex_unlock(&philo[i].mx->var);
	return (1);
}
