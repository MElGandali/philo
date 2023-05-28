/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 00:58:25 by mel-gand          #+#    #+#             */
/*   Updated: 2023/04/14 20:55:12 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"
#include <pthread.h>

int supervise_meals(t_philo *philo)
{
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

int monitor_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->mx->var);
	if ((gettime() - philo->mx->begin_time) - philo->woke_up >= philo->time_to_die)
	{
		philo->mx->dead = 1;
		pthread_mutex_unlock(&philo->mx->var);
		printf("%lld  %d died\n", gettime() - philo->mx->begin_time , philo->tid);
		return (0);
	}
	pthread_mutex_unlock(&philo->mx->var);
	return (1);
}

// void	print_action (char c, t_philo *philo)
// {
// 	if (c == 's')
// 	{
// 		pthread_mutex_lock(&philo->mx->var);
// 		if (philo->mx->dead == 0)
// 		{
// 			pthread_mutex_unlock(&philo->mx->var);
// 			printf("%lld  %d is sleeping\n", gettime() - philo->mx->begin_time, philo->tid);
// 			philo->woke_up = (gettime() - philo->mx->begin_time) + philo->time_to_sleep;
// 			ft_usleep(philo->time_to_sleep);
// 		}
// 		pthread_mutex_unlock(&philo->mx->var);
// 	}
// 	else if (c == 't')
// 	{
// 		pthread_mutex_lock(&philo->mx->var);
// 		if (philo->mx->dead == 0)
// 		{
// 			pthread_mutex_unlock(&philo->mx->var);
// 			printf("%lld  %d is thinking\n", gettime() - philo->mx->begin_time , philo->tid);
// 		}
// 		pthread_mutex_unlock(&philo->mx->var);
// 	}
// 	else if (c == 'e')
// 	{
// 		pthread_mutex_lock(&philo->mx->var);
// 		if (philo->mx->dead == 0)
// 		{
// 			pthread_mutex_unlock(&philo->mx->var);
// 			printf("%lld  %d has taken a fork\n", gettime() - philo->mx->begin_time , philo->tid);
// 			printf("%lld  %d is eating\n", gettime() - philo->mx->begin_time , philo->tid);
// 			philo->woke_up = (gettime() - philo->mx->begin_time);
// 			ft_usleep(philo->time_to_eat);
// 			philo->meals_nb--;
// 		}
// 		pthread_mutex_unlock(&philo->mx->var);
// 	}
// }

void *routini(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	
	if (philo->tid % 2 == 0)
		ft_usleep(60);
	while (1)
	{
		pthread_mutex_lock(&philo->mx->var);
		if (philo->mx->dead == 0)
		{
			pthread_mutex_unlock(&philo->mx->var);
			printf("%lld  %d is thinking\n", gettime() - philo->mx->begin_time , philo->tid);
		}
		// pthread_mutex_unlock(&philo->mx->var);
		pthread_mutex_lock(&philo->mtx);
		pthread_mutex_lock(philo->m);
		pthread_mutex_lock(&philo->mx->var);
		if (philo->mx->dead == 0)
		{
			pthread_mutex_unlock(&philo->mx->var);
			printf("%lld  %d has taken a fork\n", gettime() - philo->mx->begin_time , philo->tid);
			printf("%lld  %d is eating\n", gettime() - philo->mx->begin_time , philo->tid);
		}
		philo->woke_up = (gettime() - philo->mx->begin_time);
		ft_usleep(philo->time_to_eat);
		philo->meals_nb--;
		if (supervise_meals(philo) == 0)
			return (0);
		pthread_mutex_unlock(&philo->mtx);
		pthread_mutex_unlock(philo->m);
		
		pthread_mutex_lock(&philo->mx->var);
		if (philo->mx->dead == 0)
		{
			printf("%lld  %d is sleeping\n", gettime() - philo->mx->begin_time, philo->tid);
			pthread_mutex_unlock(&philo->mx->var);
		}
		ft_usleep(philo->time_to_sleep);
	}
	return(NULL);
}

int fill_args(int argc, char **argv, t_philo *philo)
{
	philo->nb = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo->meals_nb = ft_atoi(argv[5]);
	if (philo->time_to_die == 0 || philo->time_to_eat == 0 || philo->time_to_sleep == 0)
	{
		write (1, "Invalid Arguments\n", 18);
		return (1);
	}
	return (0);
}

int main (int argc, char **argv)
{
	t_philo philo[200];
	t_mutex mutex;
	int i;
	int meal_nb;

	i = 0;
	if (argc == 5 || argc == 6)
	{
		philo->nb = ft_atoi(argv[1]);
		mutex.counter = philo->nb;
		mutex.dead = 0;
		mutex.begin_time = gettime();
		if(philo->nb < 1 || philo->nb > 200)
		{
			write (1, "Invalid philo number\n", 22);
			return (-1);
		}
		while (i < philo->nb)
		{
			philo[i].mx = &mutex;
			i++;
		}
		i = 0;
		pthread_mutex_init(&philo->mx->var, NULL);
		while (i < philo->nb)
		{
			philo[i].tid = i + 1;
			if (fill_args(argc, argv, &philo[i]) == 1)
				return (-1);
			pthread_mutex_init(&philo[i].mtx, NULL);
			philo[i].m = &philo[(i + 1) % philo->nb].mtx;
			meal_nb = 1;
			if (argc == 6)
				meal_nb = philo->meals_nb;
			if (meal_nb == 0)
				break;
			if(pthread_create(&philo[i].th, NULL, routini, &philo[i]) != 0)
			{
				write(1, "Failed to create the thread\n", 28);
				exit(1);
			}
			i++;
		}
		// i = 0;
		// while (i < philo->nb)
		// {
		// 	pthread_mutex_destroy(&philo[i].mtx);
		// 	pthread_mutex_destroy(philo[i].m);
		// 	pthread_mutex_destroy(&philo[i].mx->meals);
		// 	i++;
		// }
		i = 0;
		while (i < philo->nb)
		{
			pthread_detach(philo[i].th);
			i++;
		}
	}
	while (1)
	{
		pthread_mutex_unlock(&philo->mx->var);
		if (monitor_death(philo) == 0 )
		{
			pthread_mutex_unlock(&philo->mx->var);
			return (0);
		}
		pthread_mutex_unlock(&philo->mx->var);
		if (mutex.counter == 0 || (meal_nb == 0 && argc == 6))
			return (0);
	}
	return (0);
}