/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:05:31 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/18 13:31:51 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_philo(t_philo *philo)
{
	cyan();
	printf("~~ PHILO %d\n", philo->id);
	black();
	printf("-> id: %d\n", philo->id);
	printf("-> time_to_die: %u\n", philo->time_to_die);
	printf("-> time_to_eat: %u\n", philo->time_to_eat);
	printf("-> time_to_sleep: %u\n", philo->time_to_sleep);
	printf("-> count_eat: %d\n", philo->count_eat);
	printf("-> state: %d\n", philo->state);
	reset();
}

void	print_philos(t_philo **philos)
{
	int	i;

	i = 0;
	cyan();
	printf("_____PHILOS TAB____\n");
	while (philos[i])
	{
		print_philo(philos[i]);
		break;
		i++;
	}
	reset();
}
