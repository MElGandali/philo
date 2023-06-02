/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:07:06 by mel-gand          #+#    #+#             */
/*   Updated: 2023/06/02 17:59:38 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

int	create_threads(t_philo *philo, int i)
{
	if (pthread_create(&philo[i].th, NULL, routini, &philo[i]) != 0)
	{
		write(1, "Failed to create the thread\n", 28);
		return (1);
	}
	return (0);
}

int	check_meals(t_philo *philo, t_mutex *mutex, int argc)
{
	pthread_mutex_lock(&philo->mx->var);
	if (mutex->counter == 0 && argc == 6)
	{
		pthread_mutex_unlock(&philo->mx->var);
		return (0);
	}
	else
		pthread_mutex_unlock(&philo->mx->var);
	return (1);
}

int	handle_threads(t_philo *philo, int argc, char **argv)
{
	int	i;

	i = 0;
	while (i < philo->nb)
	{
		philo[i].tid = i + 1;
		if (fill_args(argc, argv, &philo[i]) == 1)
			return (1);
		pthread_mutex_init(&philo[i].mtx, NULL);
		philo[i].m = &philo[(i + 1) % philo->nb].mtx;
		if (meal_nb(argc, philo) == 0)
			return (1);
		if (create_threads(philo, i) == 1)
			return (1);
		i++;
	}
	return (0);
}
