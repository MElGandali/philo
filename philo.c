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

long gettime()
{
	struct timeval current_time;
	long time;

	gettimeofday(&current_time, NULL);
	time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	return(time);
}

void	ft_usleep(int Zzz)
{
	long	start;

	start = gettime();
	usleep((Zzz - 10) * 1000);
	while (gettime() - start < Zzz)
		;
}

void *routini(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	int counter = philo->nb;

	if (philo->tid % 2 == 0)
		ft_usleep(60);
	while (1)
	{
			pthread_mutex_lock(&philo->mtx);
			pthread_mutex_lock(philo->m);
			printf("%lld  %d has taken a fork\n", gettime() - philo->begin_time, philo->tid);
			printf("%lld  %d is eating\n", gettime() - philo->begin_time, philo->tid);
			ft_usleep(philo->time_to_eat);
			philo->meals_nb--;
			if (philo->meals_nb == 0)
			{
				//printf("nmrti hya %d\n", philo->tid);
    			pthread_mutex_lock(&philo->mx->meals);
    			counter--;
			
    		if (counter == 0)
			{
        		pthread_mutex_unlock(&philo->mx->meals);
				break;
			}
			}
			pthread_mutex_unlock(&philo->mtx);
			pthread_mutex_unlock(philo->m);
			printf("%lld  %d is sleeping\n", gettime() - philo->begin_time, philo->tid);
			ft_usleep(philo->time_to_sleep);
	
	}
	return(NULL);
}

void fill_args(int argc, char **argv, t_philo *philo)
{
	philo->begin_time = gettime();
	philo->nb = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo->meals_nb = ft_atoi(argv[5]);
	if (philo->time_to_die == 0 || philo->time_to_eat == 0 || philo->time_to_sleep == 0)
	{
		write (1, "Invalid Arguments\n", 18);
		exit (1);
	}
}

int main (int argc, char **argv)
{
	pthread_t th[200];
	t_philo philo[200];
	t_mutex mutex[200];
	int i;

	i = 0;
	if (argc == 5 || argc == 6)
	{
		philo->nb = ft_atoi(argv[1]);
		if(philo->nb < 1 || philo->nb > 200)
		{
			write (1, "Invalid philo number\n", 22);
			exit (1);
		}
		while (i < philo->nb)
		{
			philo[i].tid = i + 1;
			philo[i].mx = &mutex[i];
			fill_args(argc, argv, &philo[i]);
			pthread_mutex_init(&philo[i].mtx, NULL);
			pthread_mutex_init(&philo->mx->meals, NULL);
			philo[i].m = &philo[(i + 1) % philo->nb].mtx;
			if(pthread_create(&th[i], NULL, routini, &philo[i]) != 0)
			{
				write(1, "Failed to create the thread\n", 28);
				exit(1);
			}
			i++;
			//pthread_mutex_destroy(&philo[i].mx->fork);
		}
	}
	while (1)
	{
		if (philo->meals_nb == 0)
			return (0);
	}
	return 0;
}