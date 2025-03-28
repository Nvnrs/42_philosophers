/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:24:53 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/28 16:33:35 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	philo_has_died_since_last_eat(t_table *table,
	t_philo *philo, unsigned long time_last_eat)
{
	unsigned long	actual_time;
	unsigned long	time_since_last_eat;

	actual_time = get_time_in_milliescondes();
	time_since_last_eat = (actual_time - time_last_eat);
	if (time_since_last_eat > philo->time_to_die)
	{
		pthread_mutex_lock(&table->mutex_end);
		table->end_simulation = TRUE;
		pthread_mutex_unlock(&table->mutex_end);
		print_message(DEAD, philo);
		return (TRUE);
	}
	return (FALSE);
}

void	monitor(t_table *table, t_philo **philos)
{
	unsigned int	i;
	unsigned long	time_last_eat;

	i = 0;
	while (table->number_of_philo > 0)
	{
		pthread_mutex_lock(&philos[i]->mutex_last_eat);
		time_last_eat = philos[i]->time_last_eat;
		pthread_mutex_unlock(&philos[i]->mutex_last_eat);
		if (time_last_eat > 0)
		{
			if (simulation_has_ended(table)
				|| check_philos_have_eaten(table)
				|| philo_has_died_since_last_eat(table, philos[i],
					time_last_eat))
				break ;
		}
		if (i == table->number_of_philo - 1)
			i = 0;
		else
			i++;
	}
}
