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

long gettime(t_philo *philo)
{
	gettimeofday(&philo->current_time, NULL);
	philo->t_ms = philo->current_time.tv_sec * 1000 + philo->current_time.tv_usec / 1000;
	if (philo->time == 0)
		philo->time = philo->t_ms;
	return(philo->t_ms - philo->time);	
}

void	ft_usleep(t_philo *philo)
{
	long	time;

	time = gettime(philo);
	usleep((philo->Zzz - 10) * 1000);
	while (gettime(philo) - time < philo->Zzz)
		;
}



// void supervisor(t_philo *philo)
// {
	
// }

void *routini(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	
	while (1)
	{
		sleep(1);
		printf("%ld  %d is thinking\n", gettime(philo), philo->tid);
		if (philo->tid % 2 == 0)
		{
			pthread_mutex_lock(&philo->mx->fork);
			printf("%ld  %d has taken a fork\n", gettime(philo), philo->tid);
			printf("%ld  %d is eating\n", gettime(philo), philo->tid);
			//supevisor(philo);
			pthread_mutex_unlock(&philo->mx->fork);
		}
		printf("%ld  %d is sleeping\n", gettime(philo), philo->tid);
		usleep(philo->time_to_sleep);
	}

	//return(NULL);
}

void fill_args(int argc, char **argv, t_philo *philo)
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
		exit (1);
	}
}

int main (int argc, char **argv)
{
	pthread_t th[200];
	t_philo philo[200];
	t_mutex mutex[200];
	int i;
	
	i = 1;
	if (argc == 5 || argc == 6)
	{
		philo->nb = ft_atoi(argv[1]);
		if(philo->nb < 1 || philo->nb > 200)
		{
			write (1, "Invalid philo number\n", 22);
			exit (1);
		}
		while (i <= philo->nb)
		{
			philo[i].tid = i;
			philo[i].mx = &mutex[i];
			fill_args(argc, argv, &philo[i]);
			pthread_mutex_init(&philo[i].mx->fork, NULL);
			pthread_mutex_init(&philo[i].mx->eat, NULL);
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
		//sleep(1);
	}
	return 0;
}