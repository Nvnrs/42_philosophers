/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 14:57:14 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/18 14:48:25 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	monitor(t_table *table, t_philo **philos)
{
	int	i;

	i = 0;
	(void)table;
	while (philos[i])
	{
		// 	maj for loop infinite
		if (is_last_philo(philos, i))
			i = 0;
		else
			i++;
	}
	
}

int	main(int argc, char **argv)
{
	t_philo	**philos;
	t_table	*table;

	if (!check_input(argc, argv))
		return (EXIT_FAILURE);
	table = init_table(argc, argv);
	philos = init_philos(table, argv);
	add_start_delay_philos(philos);
	assign_forks(table, philos);

	// create thread
	create_threads(philos);
	
	// monitor
	// monitor(table, philos);
	
	
	// join threads
	join_threads(philos);

	// print_table(table);
	print_philos(philos);
	free_philos(philos);
	free_table(table);
	return (EXIT_SUCCESS);
}
