/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:47:21 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/28 16:32:26 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_thread_status	routine_cases(int status, t_philo *philo, int i)
{
	if (i != 0)
		status = action(0, THINK, philo);
	if (status == THREAD_SUCCESS && philo->fork_left != NULL)
		status = take_fork_left(philo);
	if (status == THREAD_SUCCESS && philo->fork_right != NULL)
		status = take_fork_right(philo);
	if (philo->fork_right == NULL)
	{
		pthread_mutex_unlock(philo->fork_left);
		status = THREAD_DEAD;
		return (status);
	}
	if (status == THREAD_SUCCESS)
		status = eat(philo);
	if (status == THREAD_SUCCESS)
		status = action(philo->time_to_sleep, SLEEP, philo);
	return (status);
}

void	*routine(void	*philo_void)
{
	t_philo				*philo;
	t_thread_status		*status;
	int					i;

	i = 0;
	philo = philo_void;
	status = malloc(sizeof(int));
	*status = THREAD_SUCCESS;
	usleep(philo->start_delay * 1000);
	pthread_mutex_lock(&philo->mutex_last_eat);
	philo->time_last_eat = get_time_in_milliescondes();
	pthread_mutex_unlock(&philo->mutex_last_eat);
	if (philo->table->required_eats_per_philo == 0)
		*status = THREAD_END;
	while (*status == THREAD_SUCCESS)
	{
		*status = routine_cases(*status, philo, i);
		i++;
	}
	return (status);
}
