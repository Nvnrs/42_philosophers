/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:42:49 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/28 16:32:19 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_threads(t_philo **philos)
{
	int	i;

	i = 0;
	while (philos[i])
	{
		pthread_create(&philos[i]->thread, NULL,
			routine, philos[i]);
		i++;
	}
}

void	add_start_delay_philos(t_philo **philos)
{
	int	i;

	i = 0;
	if (len_tab((void **)philos) == 1)
		return ;
	while (philos[i])
	{
		if (i % 2 != 0)
		{
			philos[i]->start_delay = philos[i]->time_to_eat;
		}
		i++;
	}
}
