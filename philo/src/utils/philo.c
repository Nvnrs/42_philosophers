/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:00:33 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/19 23:37:29 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	is_last_philo(t_philo **philos, int i)
{
	if ((philos[i] && philos[i + 1] == NULL))
		return (TRUE);
	return (FALSE);
}

t_bool	philo_is_dead(t_philo *philo)
{
	unsigned	long time_since_last_eat;

	time_since_last_eat = (get_time_in_milliescondes() - philo->time_last_eat);
	// print_philo(philo);
	// printf("TIME _SINCE _LAST EAT : %lu\n", time_since_last_eat);
	if (time_since_last_eat >= philo->time_to_die)
	{
		philo->state = DEAD;
		return (TRUE);
	}
	return (FALSE);
}