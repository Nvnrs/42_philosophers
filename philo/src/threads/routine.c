/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:47:21 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/22 17:16:28 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_thread_status	routine_cases(int  status, t_philo *philo)
{
	status = action(0, THINK, philo);
	if (status == THREAD_SUCCESS && philo->fork_left != NULL)
		status = action(0, FORK, philo);
	if (status == THREAD_SUCCESS && philo->fork_right != NULL)
		status = action(0, FORK, philo);
	if (status == THREAD_SUCCESS &&  philo->fork_left && philo->fork_right)
		status = eat(philo);
	if (status == THREAD_SUCCESS &&  philo->fork_left && philo->fork_right)
		status = action(philo->time_to_sleep, SLEEP, philo);
	if (philo->fork_left == NULL || philo->fork_right == NULL)
		status = THREAD_DEAD;
	// print_table(philo->table);
	return (status);
}

void	*routine(void	*philo_void)
{
	t_philo				*philo;
	t_thread_status		*status;

	philo = philo_void;
	status = malloc(sizeof(int));
	*status = THREAD_SUCCESS;
	usleep(philo->start_delay * 1000);
	philo->time_last_eat = get_time_in_milliescondes();
	while (*status == THREAD_SUCCESS)
	{
		*status = routine_cases(*status, philo);
	}
	if (*status != THREAD_SUCCESS)
	{
		if (simulation_has_ended(philo->table)
		|| check_philos_have_eaten(philo->table))
			*status = THREAD_END;
	}
	return (status);
}
