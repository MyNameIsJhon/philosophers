/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 17:47:18 by jriga             #+#    #+#             */
/*   Updated: 2025/09/27 20:49:10 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "philo.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	*ft_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	data = ((t_philo *)arg)->data;
	philo = (t_philo *)arg;
	for (int i = 0; i < philo->data->number_of_meals ; i++)
	{
		(void)i;
		philo_eat(philo);
		philo_sleep(philo);
		if (philo->is_dead)
			break ;
	}
	pthread_mutex_lock(&data->ended_threads_lock);
	data->ended_threads++;
	pthread_mutex_unlock(&data->ended_threads_lock);
	return (NULL);
}

static void	init_forks(pthread_mutex_t **forks, int number_of_philosophers)
{
	int	i;

	*forks = malloc(sizeof(pthread_mutex_t) * number_of_philosophers);
	i = 0;
	while (i < number_of_philosophers)
	{
		pthread_mutex_init(&(*forks)[i], NULL);
		i++;
	}
}

static void	init_philosophers(t_philo **philos, pthread_mutex_t **forks,
		int number_of_philosophers, t_data *data)
{
	int	i;

	i = 0;
	*philos = malloc(sizeof(t_philo) * number_of_philosophers);
	while (i < number_of_philosophers)
	{
		(*philos)[i].id = i + 1;
		(*philos)[i].last_meal = timestamp_ms() * 1000;
		(*philos)[i].meals_eaten = 0;
		(*philos)[i].left_fork = &(*forks)[i];
		(*philos)[i].right_fork = &(*forks)[(i + 1) % number_of_philosophers];
		(*philos)[i].data = data;
		(*philos)[i].is_dead = 0;
		i++;
	}
}

static t_data	*init_data(char **args)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	pthread_mutex_init(&data->print_lock, NULL);
	pthread_mutex_init(&data->ended_threads_lock, NULL);
	data->start_time = timestamp_ms();
	data->number_of_philosophers = ft_atoi(args[0]);
	data->time_to_die = ft_atoi(args[1]) * 1000LL;
	data->time_to_eat = ft_atoi(args[2]) * 1000LL;
	data->time_to_sleep = ft_atoi(args[3]) * 1000LL;
	data->ended_threads = 0;
	return (data);
}

t_philo	*init_philos(char **args)
{
	t_philo	*philos;
	t_data	*data;
	int		ac;

	data = init_data(args);
	ac = ft_strslen(args);
	if (ac == 5)
		data->number_of_meals = ft_atoi(args[4]);
	else
		data->number_of_meals = -1;
	init_forks(&data->forks, data->number_of_philosophers);
	init_philosophers(&philos, &data->forks, data->number_of_philosophers,
		data);
	return (philos);
}
