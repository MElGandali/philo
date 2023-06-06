/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 00:58:28 by mel-gand          #+#    #+#             */
/*   Updated: 2023/04/14 02:09:31 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include<stdio.h>
# include<unistd.h>
# include<stdlib.h>
# include<pthread.h>
# include<sys/time.h>
# include<limits.h>

typedef struct mutex
{
	int				counter;
	int				dead;
	long long		begin_time;
	pthread_mutex_t	var;
}			t_mutex;

typedef struct s_philosopher
{
	int				time;
	int				nb;
	int				tid;
	t_mutex			*mx;
	pthread_t		th;
	pthread_mutex_t	*m;
	pthread_mutex_t	mtx;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_nb;
	int				ate;
}			t_philo;

long long	ft_atoi(char *str);
void		init_var(t_philo *philo, t_mutex *mutex);
int			meal_nb(int argc, t_philo *philo);
int			input_error(t_philo *philo, char **argv);
int			ft_isalnum(int n);
int			handle_threads(t_philo *philo, int argc, char **argv);
int			check_meals(t_philo *philo, t_mutex *mutex, int argc);
int			create_threads(t_philo *philo, int i);
int			fill_args(int argc, char **argv, t_philo *philo);
void		*routini(void *arg);
long		gettime(void);
int			ft_usleep(t_philo *philo, int time);
int			print_think(t_philo *philo);
int			print_sleep(t_philo *philo);
int			print_eat(t_philo *philo);
int			print_all(t_philo *philo, char *str);
int			supervise_meals(t_philo *philo);
int			monitor_death(t_philo *philo, int i);
void		destroy_mutexes(t_philo *philo);
void		detach_threads(t_philo *philo);

#endif