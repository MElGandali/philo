/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 23:28:38 by mel-gand          #+#    #+#             */
/*   Updated: 2023/05/26 18:37:18 by mel-gand         ###   ########.fr       */
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

void	ft_usleep(int time)
{
	long	start;

	start = gettime();
	while (gettime() - start < time)
		;
}