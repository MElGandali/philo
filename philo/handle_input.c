/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:29:25 by mel-gand          #+#    #+#             */
/*   Updated: 2023/06/04 15:00:10 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"
#include <limits.h>

int	args_error(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (ft_isalnum(argv[i][j]) == 0)
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

int	min_max_error(char **argv)
{
	long int	i;

	i = 1;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) > INT_MAX || ft_atoi(argv[i]) < INT_MIN)
			return (-1);
		i++;
	}
	return (0);
}

int	input_error(t_philo *philo, char **argv)
{
	if (philo->nb < 1 || philo->nb > 200 || args_error(argv) == -1
		|| min_max_error(argv) == -1)
	{
		write(2, "Error\n", 6);
		return (-1);
	}
	return (0);
}

int	meal_nb(int argc, t_philo *philo)
{
	int	meal_nb;

	meal_nb = 0;
	if (argc == 6)
	{
		meal_nb = philo->meals_nb;
		if (meal_nb == 0)
			return (0);
	}
	return (1);
}
