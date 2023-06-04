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

void	*routini(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->woke_up = 0;
	if (philo->tid % 2 == 0)
		usleep(60);
	while (1)
	{
		if (print_think(philo) == 1)
			return (0);
		pthread_mutex_lock(&philo->mtx);
		if (print_all(philo, "has taken a fork") == 1)
			return (0);
		pthread_mutex_lock(philo->m);
		if (print_eat(philo) == 1)
			return (0);
		if (supervise_meals(philo) == 0)
			return (0);
		pthread_mutex_unlock(&philo->mtx);
		pthread_mutex_unlock(philo->m);
		if (print_sleep(philo) == 1)
			return (0);
	}
	return (0);
}

int	fill_args(int argc, char **argv, t_philo *philo)
{
	philo->nb = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo->meals_nb = ft_atoi(argv[5]);
	if (philo->time_to_die == 0 || philo->time_to_eat == 0
		|| philo->time_to_sleep == 0)
	{
		write (1, "Invalid Arguments\n", 18);
		return (1);
	}
	return (0);
}

void	check_threads(t_philo *philo, t_mutex mutex, int argc)
{
	int	i;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&philo[i].mx->var);
		if (monitor_death(philo, i) == 0)
			break ;
		if (check_meals(philo, &mutex, argc) == 0)
			break ;
		i++;
		if (i == philo->nb)
			i = 0;
	}
	detach_threads(philo);
	destroy_mutexes(philo);
}

int	main(int argc, char **argv)
{
	t_philo	philo[250];
	t_mutex	mutex;

	if (argc == 5 || argc == 6)
	{
		philo->nb = ft_atoi(argv[1]);
		if (input_error(philo, argv) == -1)
			return (1);
		init_var(philo, &mutex, argv);
		pthread_mutex_init(&philo->mx->var, NULL);
		if (handle_threads(philo, argc, argv) == 1)
			return (1);
		check_threads(philo, mutex, argc);
	}
	return (0);
}
