/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 14:57:14 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/19 23:48:36 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	philos_have_eaten(t_table *table, t_philo **philos)
{
	unsigned int	i;
	unsigned int philo_validate_meal;

	i = 0;
	philo_validate_meal = 0;
	while (philos[i])
	{
		if (philos[i]->count_eat >= table->required_eats_per_philo)
			philo_validate_meal++;
		i++;
	}
	if (philo_validate_meal == table->number_of_philo)
		return (TRUE);
	// print_philos(philos);
	// print_table(table);
	return (FALSE);
}

// void	print_message()
// {
	
// }

void	monitor(t_table *table, t_philo **philos)
{
	int	i;
	int state;

	i = 0;
	(void)table;
	while (1)
	{
		state = philos[i]->state;
		if (philos_have_eaten(table, philos))
		{
			print_philos(philos);
			exit(1);
		}
		// if (state != states_philos[i])
		// {
		// 	printf("timestamp in ms ");
		// 	printf("%d ", philos[i]->id);
		// 	if (state == SLEEP)
		// 		printf("is sleeping");
		// 	if (state == EAT)
		// 		printf("is eating");
		// 	if (state == THINK)
		// 		printf("is thinking");
		// 	printf("\n");
		// 	states_philos[i] = state;
		// }
		if (is_last_philo(philos, i))
			i = 0;
		else
			i++;
	}
}
int	*state_of_philo_to_tab(t_philo **philos)
{
	int *tab;
	int	i;

	i = 0;
	tab = malloc(len_tab(((void**)philos)) * sizeof(int));
	while (philos[i])
	{
		tab[i] = philos[i]->state;
		i++;
	}
	return (tab);
}
void	print_tab_state(int *tab, int max)
{
	int	i;

	i = 0;
	cyan();
	printf("______TAB OF STATES PHILO______\n");
	black();
	while (i < max)
	{
		printf("-> tab[%d]: %d\n", i, tab[i]);
		i++;
	}
	reset();
}

unsigned long	get_time_in_milliescondes()
{
	struct timeval time;
	gettimeofday(&time , NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	main(int argc, char **argv)
{
	t_philo	**philos;
	t_table	*table;

	if (!check_input(argc, argv))
		return (EXIT_FAILURE);
	table = init_table(argc, argv);
	philos = init_philos(table, argv);

	print_philos(philos);
	print_table(table);
	assign_forks(table, philos);
	// create thread
	create_threads(philos);
	
	// monitor
	// monitor(table, philos);


	join_threads(philos);
	free_philos(philos);
	free_table(table);
	return (EXIT_SUCCESS);
}
