/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 17:48:17 by jriga             #+#    #+#             */
/*   Updated: 2025/09/27 17:49:47 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdio.h>
#include "philo.h"

long long    timestamp_ms(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000);
}

void philo_print(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->print_lock);
	printf("%lld %d %s\n", timestamp_ms() - philo->data->start_time, philo->id, str);
	pthread_mutex_unlock(&philo->data->print_lock);
}
