/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:40:29 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/22 14:01:12 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	assign_forks(t_table *table, t_philo **philos)
{
	int	i;

	i = 0;
	while (philos[i])
	{
		if ((len_tab((void **)philos) % 2) != 0
			&& is_last_philo(philos, i))
		{
			if ((i - 1 ) < 0)
				philos[i]->fork_left = NULL;
			else
				philos[i]->fork_left = table->forks[i - 1];
			philos[i]->fork_right = table->forks[i];
			i++;
			continue ;
		}
		if (is_last_philo(philos, i))
		{
			philos[i]->fork_left =  table->forks[0];
			philos[i]->fork_right = table->forks[i];
			
		}
		else
		{
			philos[i]->fork_left =  table->forks[i];
			philos[i]->fork_right = table->forks[i + 1];
		}
		i++;
	}
}
