/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 14:07:59 by jriga             #+#    #+#             */
/*   Updated: 2025/09/27 18:27:47 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
#include <pthread.h>

typedef struct s_data
{
	int				number_of_philosophers;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				number_of_meals;
	pthread_mutex_t	print_lock;
	long long		start_time;
	pthread_mutex_t	*forks;
}	t_data;

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	long long		last_meal;
	int				meals_eaten;
	t_data			*data;
}	t_philo;

long long	timestamp_ms(void);
void		philo_print(t_philo *philo, char *str);
void		*ft_routine(void *arg);
t_philo		*init_philos(char **args);
void		philo_eat(t_philo *philo);
void		philo_sleep(t_philo *philo);
#endif
