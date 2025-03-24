/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:45:20 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/24 18:07:32 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	check_philos_have_eaten(t_table *table)
{
	int		total_eats;
	t_bool	have_eaten;

	if (table->required_eats_per_philo < 0)
		return (FALSE);
	pthread_mutex_lock(&table->mutex_count_eat);
	have_eaten = FALSE;
	total_eats = table->required_eats_per_philo * (int)table->number_of_philo;
	if (table->count_eat >= total_eats)
		have_eaten = TRUE;
	pthread_mutex_unlock(&table->mutex_count_eat);
	return (have_eaten);
}


t_bool	simulation_has_ended(t_table *table)
{
	t_bool	end;

	end = FALSE;
	pthread_mutex_lock(&table->mutex_end);
	if (table->end_simulation)
		end = TRUE;
	pthread_mutex_unlock(&table->mutex_end);
	return (end);
}


void	join_threads(t_philo **philos, t_table *table)
{
	int		i;
	t_thread_status	*return_val;

	i = 0;
	while (philos[i])
	{
		pthread_join(philos[i]->thread, (void **)&return_val);
		if (*return_val == THREAD_DEAD && !simulation_has_ended(table))
		{
			pthread_mutex_lock(&table->mutex_end);
			table->end_simulation = TRUE;
			pthread_mutex_unlock(&table->mutex_end);
			print_message(DEAD, philos[i]);
		}
		free((void *)return_val);
		i++;
	}
}
