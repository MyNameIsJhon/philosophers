/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 18:16:50 by jriga             #+#    #+#             */
/*   Updated: 2025/09/27 19:48:23 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <unistd.h>

void philo_sleep(t_philo *philo)
{
	philo_print(philo, "is sleeping");
	usleep(philo->data->time_to_sleep);
}

void philo_death(t_philo *philo, long time_add)
{
	if (timestamp_ms() - philo->last_meal + time_add >= philo->data->time_to_die)
	{
		usleep(philo->data->time_to_die);
	}
}

void philo_eat(t_philo *philo)
{
	philo_print(philo, "is thinking");
	pthread_mutex_lock(philo->left_fork);
	philo_print(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	philo_print(philo, "is eating");
	philo->last_meal = timestamp_ms();
	philo->meals_eaten++;
	usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}
