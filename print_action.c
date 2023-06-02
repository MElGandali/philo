/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 16:17:43 by mel-gand          #+#    #+#             */
/*   Updated: 2023/06/02 17:46:38 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

int	print_all(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->mx->var);
	if (philo->mx->dead == 0)
	{
		pthread_mutex_unlock(&philo->mx->var);
		pthread_mutex_lock(&philo->mx->var);
		printf("%lld  %d %s\n", gettime()
			- philo->mx->begin_time, philo->tid, str);
		pthread_mutex_unlock(&philo->mx->var);
	}
	else
	{
		pthread_mutex_unlock(&philo->mx->var);
		return (1);
	}
	return (0);
}

int	print_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->mx->var);
	if (philo->mx->dead == 0)
	{
		pthread_mutex_unlock(&philo->mx->var);
		if (print_all(philo, "is thinking") == 1)
			return (1);
	}
	else
	{
		pthread_mutex_unlock(&philo->mx->var);
		return (1);
	}
	return (0);
}

int	print_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->mx->var);
	if (philo->mx->dead == 0)
	{
		pthread_mutex_unlock(&philo->mx->var);
		if (print_all(philo, "has taken a fork") == 1)
			return (1);
		if (print_all(philo, "is eating") == 1)
			return (1);
		pthread_mutex_lock(&philo->mx->var);
		philo->woke_up = (gettime() - philo->mx->begin_time);
		pthread_mutex_unlock(&philo->mx->var);
		if (ft_usleep(philo, philo->time_to_eat) == 1)
			return (1);
	}
	else
	{
		pthread_mutex_unlock(&philo->mx->var);
		return (1);
	}
	return (0);
}

int	print_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->mx->var);
	if (philo->mx->dead == 0)
	{
		pthread_mutex_unlock(&philo->mx->var);
		if (print_all(philo, "is sleeping") == 1)
			return (1);
		if (ft_usleep(philo, philo->time_to_sleep) == 1)
			return (1);
	}
	else
	{
		pthread_mutex_unlock(&philo->mx->var);
		return (1);
	}
	return (0);
}
