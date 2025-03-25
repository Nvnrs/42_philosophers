/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:46:31 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/25 10:36:36 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_action state, t_philo *philo)
{
	unsigned long	current_time;

	pthread_mutex_lock(&philo->table->write_access);
	current_time = get_time_in_milliescondes() - philo->table->time_at_start;
	if (state == SLEEP)
		printf(SLEEP_MESSAGE, current_time, philo->id);
	if (state == EAT)
		printf(EAT_MESSAGE, current_time, philo->id);
	if (state == THINK)
		printf(THINK_MESSAGE, current_time, philo->id);
	if (state == FORK)
		printf(FORK_MESSAGE, current_time, philo->id);
	if (state == DEAD)
		printf(DEAD_MESSAGE, current_time, philo->id);
	pthread_mutex_unlock(&philo->table->write_access);
}

t_thread_status	take_fork_left(t_philo *philo)
{
	t_thread_status	status;

	pthread_mutex_lock(philo->fork_left);
	status = action(0, FORK, philo);
	if (status != THREAD_SUCCESS)
	{
		pthread_mutex_unlock(philo->fork_left);
		return (status);
	}
	return (status);
}

t_thread_status	take_fork_right(t_philo *philo)
{
	t_thread_status	status;

	pthread_mutex_lock(philo->fork_right);
	status = action(0, FORK, philo);
	if (status != THREAD_SUCCESS)
	{
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
		return (status);
	}
	return (status);
}

t_thread_status	eat(t_philo *philo)
{
	if (simulation_has_ended(philo->table)
		|| check_philos_have_eaten(philo->table))
	{
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
		return (THREAD_END);
	}
	philo->time_last_eat = get_time_in_milliescondes();
	print_message(EAT, philo);
	if (sleep_and_check_dead(philo->time_to_eat, philo) != THREAD_SUCCESS)
	{
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
		return (THREAD_DEAD);
	}
	pthread_mutex_lock(&philo->table->mutex_count_eat);
	philo->table->count_eat++;
	pthread_mutex_unlock(&philo->table->mutex_count_eat);
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
	return (THREAD_SUCCESS);
}

t_thread_status	action(unsigned long action_time,
	t_action action, t_philo *philo)
{
	if (simulation_has_ended(philo->table)
		|| check_philos_have_eaten(philo->table))
		return (THREAD_END);
	print_message(action, philo);
	if (sleep_and_check_dead(action_time, philo) != THREAD_SUCCESS)
		return (THREAD_DEAD);
	return (THREAD_SUCCESS);
}
