/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 14:57:14 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/18 13:33:38 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	is_last_philo(t_philo **philos, int i)
{
	if ((philos[i] && philos[i + 1] == NULL))
		return (TRUE);
	return (FALSE);
}

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
			// printf("fork_left : %s", i - 1);
			// printf("fork_right : %d", i);
			i++;
			continue ;
		}
		// printf("fork_right : %d\n", i);
		// printf("fork_left : %d\n", i + 1);
		philos[i]->fork_left =  table->forks[i];
		if (is_last_philo(philos, i))
			philos[i]->fork_right = NULL;
		else
			philos[i]->fork_right = table->forks[i + 1];
		
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
	assign_forks(table, philos);
	print_table(table);
	print_philos(philos);
	free_philos(philos);
	free_table(table);
	return (EXIT_SUCCESS);
}
