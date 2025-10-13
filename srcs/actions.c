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

#include <philo.h>
#include <unistd.h>

void	philo_sleep(t_philo *philo)
{
	philo_print(philo, "is sleeping");
	usleep(philo->data->time_to_sleep);
}

void	*monitor(t_philo *philo)
{
	int	lim;
	int	i;
	int	counter;

	lim = philo->data->number_of_philosophers;
	i = 0;
	counter = 0;
	while (1)
	{
		usleep(5000);
		while (i < lim)
		{
			if (timestamp_ms() - philo[i].last_meal > philo->data->time_to_die
				&& !philo->is_dead)
			{
				philo_print(&philo[i], "died");
				philo[i].is_dead = 1;
				counter++;
				if (counter == lim)
					return (NULL);
			}
			i++;
		}
		i = 0;
	}
}

void	philo_eat(t_philo *philo)
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
