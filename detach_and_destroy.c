/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detach_and_destroy.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 23:01:15 by mel-gand          #+#    #+#             */
/*   Updated: 2023/05/30 19:09:03 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	destroy_mutexes(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->nb)
	{
		pthread_mutex_destroy(&philo[i].mtx);
		pthread_mutex_destroy(philo[i].m);
		pthread_mutex_destroy(&philo[i].mx->var);
		i++;
	}
}

void	detach_threads(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->nb)
	{
		pthread_detach(philo[i].th);
		i++;
	}
}
