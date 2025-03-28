/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:40:29 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/28 16:01:57 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	fork_for_last_philo_when_philos_odd(t_table *table,
	t_philo **philos, int i)
{
	if ((i - 1) < 0)
	{
		philos[i]->fork_left = NULL;
		printf("fork_left : NULL\n", NULL);
	}
	else
	{
		philos[i]->fork_left = table->forks[i - 1];
		printf("fork_left : %d\n", i - 1);

	}
	philos[i]->fork_right = table->forks[i];
	printf("fork_right : %d\n", i);
}

void	assign_forks(t_table *table, t_philo **philos)
{
	int	i;

	i = 0;
	while (philos[i])
	{
		printf("PHILO : %d\n", i);
		if (len_tab((void **)philos) == 1)
		{
			philos[i]->fork_left = table->forks[i];
			philos[i]->fork_right = NULL;
			break;
		}
		// 	fork_for_last_philo_when_philos_odd(table, philos, i);
		if (is_last_philo(philos, i))
		{
			philos[i]->fork_left = table->forks[0];
			philos[i]->fork_right = table->forks[i];
			printf("	fork_left : %d\n", 0);
			printf("	fork_right : %d\n", i);
		}
		else
		{
			philos[i]->fork_left = table->forks[i];
			philos[i]->fork_right = table->forks[i + 1];
			printf("	fork_left : %d\n", i);
			printf("	fork_right : %d\n", i+ 1);
		}

		// if (i % 2 == 0)
		// {
		// 	if (i == (len_tab((void **)philos) - 1))
		// 	{
		// 		philos[i]->fork_left = table->forks[i];
		// 		philos[i]->fork_right = table->forks[0];
		// 		printf("	fork_left : %d\n", i);
		// 		printf("	fork_right : %d\n", 0);
		// 	}
		// 	else
		// 	{
		// 		philos[i]->fork_left = table->forks[i];
		// 		philos[i]->fork_right = table->forks[i + 1];
		// 		printf("	fork_left : %d\n", i);
		// 		printf("	fork_right : %d\n", i + 1);
		// 	}
		// }
		// else
		// {
		// 	philos[i]->fork_left = table->forks[i - 1];
		// 	philos[i]->fork_right = table->forks[i];
		// 	printf("	fork_left : %d\n", i - 1);
		// 	printf("	fork_right : %d\n", i);
		// }
		i++;
	}
}
