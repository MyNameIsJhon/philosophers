/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 13:16:50 by jriga             #+#    #+#             */
/*   Updated: 2025/09/27 13:52:39 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include <sys/_pthread/_pthread_mutex_t.h>
#include <unistd.h>
#include "libft.h"

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	long long		last_meal;
	int				meals_eaten;
}	t_philo;

typedef struct s_data
{
	int				number_of_philosophers;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				number_of_meals;
	pthread_mutex_t	print_lock;
	long long		start_time;
	t_philo			*philos;
	pthread_mutex_t	*forks;
}	t_data;

void	*ft_routine(void *arg)
{
	(void)arg;
	
	while (1)
	{
		// Thinking
		// Picking up forks
		// Eating
		// Putting down forks
		// Sleeping
	}
}

void init_forks(pthread_mutex_t **forks, int number_of_philosophers)
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

void ft_init_philosophers(t_philo **philos, pthread_mutex_t **forks, int number_of_philosophers)
{
	int	i;
	i = 0;
	
	*philos = malloc(sizeof(t_philo) * number_of_philosophers);
	while (i < number_of_philosophers - 1)
	{
		philos[i]->id = i + 1;
		philos[i]->last_meal = 0;
		philos[i]->meals_eaten = 0;
		philos[i]->left_fork = &(*forks)[i];
		philos[i]->right_fork = &(*forks)[(i + 1) % number_of_philosophers];
		i++;
	}
}

int main(int ac, char **av)
{
	pthread_t		*threads;
	/* t_philo			*philos; */
	int				number_of_philosophers;
	/* pthread_mutex_t	*forks; */

	if (ac != 5 && ac != 6)
		return (1);
	number_of_philosophers = ft_atoi(av[1]);
	ft_printf("Number of philosophers: %d\n", number_of_philosophers);
	/* philos = malloc(sizeof(t_philo) * number_of_philosophers); */
	if (!threads)
		return (1);
	while (--number_of_philosophers >= 0)
		pthread_create(&threads[number_of_philosophers], NULL, ft_routine, NULL);
}
