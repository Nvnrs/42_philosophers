/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:32:07 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/19 03:25:35 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	unsigned	long time;

	time = philo->time_to_eat * 1000;
	pthread_mutex_lock(philo->fork_left);
	pthread_mutex_lock(philo->fork_right);
	philo->state = EAT;
	philo->count_eat++;
	usleep(time);
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
}

void	action(unsigned long action_time, t_state action, t_philo *philo)
{
	unsigned	long time;

	time = action_time * 1000;
	philo->state = action;
	usleep(time);
}

void	*routine(void	*philo_void)
{
	t_philo	*philo;

	philo = philo_void;
	// printf("HELLO FROM thread %d\n", philo->id);
	while (1)
	{
		philo->state = THINK;
		action(0, THINK, philo);
		eat(philo);
		action(philo->time_to_sleep, SLEEP, philo);
	}
	
	return (NULL);
}

void	create_threads(t_philo **philos)
{
	int	i;

	i = 0;
	while (philos[i])
	{
		usleep(philos[i]->start_delay * 1000);
		pthread_create(&philos[i]->thread, NULL,
			routine, philos[i]);
		i++;
	}
}

void	join_threads(t_philo **philos)
{
	int	i;

	i = 0;
	while (philos[i])
	{
		pthread_join(philos[i]->thread, NULL);
		i++;
	}
}

void	add_start_delay_philos(t_philo **philos)
{
	int	i;

	i = 0;
	if (len_tab((void **)philos) == 1)
		return;
	while (philos[i])
	{
		if (is_last_philo(philos, i)				
		&& len_tab((void **)philos) % 2 != 0)
		{
			philos[i]->start_delay = (philos[i]->time_to_eat * 2);
		}
		else if (i % 2 != 0)
		{
			philos[i]->start_delay = philos[i]->time_to_eat;
		}
		i++;
	}
}
