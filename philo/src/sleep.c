/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 20:25:08 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/21 17:01:53 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


t_bool	philo_is_dead_pending_action(t_philo *philo, long time_action)
{
	unsigned	long time_since_last_eat;

	time_since_last_eat = (get_time_in_milliescondes() - philo->time_last_eat);
	// printf("TIME _SINCE _LAST EAT : %lu\n", time_since_last_eat);
	// black();
	// printf("tinme action %ld\n", time_action);
	// printf("since last eat %ld\n", time_since_last_eat);
	// printf("lat + time : %ld\n", time_action + time_since_last_eat);
	// printf("lat + time : %ld\n", time_action + time_since_last_eat);
	// reset();
	if ((time_since_last_eat + time_action) > philo->time_to_die)
	{
		philo->state = DEAD;
		return (TRUE);
	}
	return (FALSE);
}

t_status	sleep_and_check_dead(long time_action, t_philo *philo, t_bool check_dead)
{
	if (check_dead && philo_is_dead_pending_action(philo, time_action))
	{
		usleep(philo->time_to_die * 1000);
		return (THREAD_DEAD);
	}
	usleep(time_action * 1000);
	return (THREAD_SUCCESS);
}

// int	main(void)
// {
// 	custom_sleep(231123);
// 	return (0);
// }