/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 13:16:50 by jriga             #+#    #+#             */
/*   Updated: 2025/09/27 20:47:54 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "philo.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/_pthread/_pthread_t.h>
#include <unistd.h>

int	monitor(t_philo *philos, long long time_to_die)
{
	int max;
	int i;
	t_data *data;
	long long time;

	data = philos->data;
	max = data->number_of_philosophers;
	(void)data;
	while (data->ended_threads < max)
	{
		i = 0;
		usleep(10000);
		while (i < max)
		{
			time = timestamp_ms() * 1000;
			if (time - philos[i].last_meal > time_to_die && !philos[i].is_dead)
			{
				philos[i].is_dead = 1;
				philo_print(&philos[i], "died");
			}
			i++;
		}
	}
	return (0);
}

int	main(int ac, char **av)
{
	pthread_t	*threads;
	t_philo		*philos;
	int			number_of_philosophers;
	long long	time_to_die;
	/* t_data		*data; */

	/* pthread_mutex_t	*forks; */
	if (ac != 5 && ac != 6)
	{
		ft_printf("Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]");
		return (1);
	}
	philos = init_philos(av + 1);
	number_of_philosophers = philos->data->number_of_philosophers;
	time_to_die = philos->data->time_to_die;
	printf("time to die: %lld\n", time_to_die);
	threads = malloc(sizeof(pthread_t) * number_of_philosophers);
	while (--number_of_philosophers >= 0)
		pthread_create(&threads[number_of_philosophers], NULL, ft_routine,
			&philos[number_of_philosophers]);
	while (++number_of_philosophers < philos->data->number_of_philosophers)
		pthread_detach(threads[number_of_philosophers]);
	monitor(philos, time_to_die);
	return (0);
}
