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
#include <unistd.h>

int	main(int ac, char **av)
{
	pthread_t	*threads;
	t_philo		*philos;
	int			number_of_philosophers;

	/* pthread_mutex_t	*forks; */
	if (ac != 5 && ac != 6)
		return (1);
	philos = init_philos(av + 1);
	number_of_philosophers = philos->data->number_of_philosophers;
	threads = malloc(sizeof(pthread_t) * number_of_philosophers);
	while (--number_of_philosophers >= 0)
		pthread_create(&threads[number_of_philosophers], NULL, ft_routine,
			&philos[number_of_philosophers]);
	while (++number_of_philosophers < philos->data->number_of_philosophers)
		pthread_join(threads[number_of_philosophers], NULL);
	pthread_create(&threads[0], NULL, (void *)monitor, philos);
	pthread_detach(threads[0]);
	return (0);
}
