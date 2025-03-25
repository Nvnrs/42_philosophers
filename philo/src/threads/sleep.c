/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 20:25:08 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/25 10:37:02 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	philo_is_dead_pending_action(t_philo *philo, unsigned long time_action,
		unsigned long time_since_last_eat)
{
	if ((time_since_last_eat + time_action) > philo->time_to_die)
		return (TRUE);
	return (FALSE);
}

t_bool	philo_is_dead_before_action(t_philo *philo,
	unsigned long time_since_last_eat)
{
	if (time_since_last_eat > philo->time_to_die)
		return (TRUE);
	return (FALSE);
}

t_thread_status	sleep_and_check_dead(long time_action,
	t_philo *philo)
{
	unsigned long	actual_time;
	unsigned long	time_since_last_eat;
	unsigned long	time_left_before_death;

	actual_time = get_time_in_milliescondes();
	time_since_last_eat = (actual_time - philo->time_last_eat);
	if (philo_is_dead_before_action(philo, time_since_last_eat))
		return (THREAD_DEAD);
	if (philo_is_dead_pending_action(philo, time_action, time_since_last_eat))
	{
		time_left_before_death = philo->time_to_die - time_since_last_eat;
		usleep(time_left_before_death * 1000);
		return (THREAD_DEAD);
	}
	usleep(time_action * 1000);
	return (THREAD_SUCCESS);
}
