/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 18:16:50 by jriga             #+#    #+#             */
/*   Updated: 2025/09/27 20:44:51 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <philo.h>
#include <unistd.h>

void	philo_sleep(t_philo *philo)
{
	if (philo->is_dead)
		return ;
	philo_print(philo, "is sleeping");
	usleep(philo->data->time_to_sleep);
}

void	philo_eat(t_philo *philo)
{
	if (philo->is_dead)
		return ;
	philo_print(philo, "is thinking");
	if (philo->is_dead)
		return ;
	pthread_mutex_lock(philo->left_fork);
	philo_print(philo, "has taken a fork");
	if (philo->is_dead)
	{
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	pthread_mutex_lock(philo->right_fork);
	philo_print(philo, "is eating");
	philo->last_meal = timestamp_ms() * 1000;
	philo->meals_eaten++;
	usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}
