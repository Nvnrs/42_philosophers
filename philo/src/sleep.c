/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 20:25:08 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/21 14:03:34 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_remove_val(long time)
{
	long	remove;

	if (time >= 5000)
		remove = 500;
	else if (time >= 1000)
		remove = 100;
	else if (time >= 100)
		remove = 100;
	else if (time < 100 && (time - 10 ) > 0)
		remove = 10;
	else
		remove = 1;
	return (remove);
}

t_bool	philo_is_dead_pending_action(t_philo *philo, long time_action)
{
	unsigned	long time_since_last_eat;

	time_since_last_eat = (get_time_in_milliescondes() - philo->time_last_eat);
	// printf("TIME _SINCE _LAST EAT : %lu\n", time_since_last_eat);
	black();
	printf("tinme action %ld\n", time_action);
	printf("since last eat %ld\n", time_since_last_eat);
	printf("lat + time : %ld\n", time_action + time_since_last_eat);
	printf("lat + time : %ld\n", time_action + time_since_last_eat);
	reset();
	if ((time_since_last_eat + time_action) > philo->time_to_die)
	{
		philo->state = DEAD;
		return (TRUE);
	}
	return (FALSE);
}

t_status	custom_sleep(long time_action, t_philo *philo, t_bool check_dead)
{

	if (check_dead && philo_is_dead(philo))
			return (FAIL);
	if (check_dead && philo_is_dead_pending_action(philo, time_action))
	{
		usleep(philo->time_to_die * 1000);
		return (FAIL);
	}
	usleep(time_action * 1000);
	return (SUCCESS);
}

// int	main(void)
// {
// 	custom_sleep(231123);
// 	return (0);
// }