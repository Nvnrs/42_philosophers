/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:58:51 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/21 15:29:50 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*init_fork()
{
	pthread_mutex_t	*fork;

	fork = malloc(sizeof(pthread_mutex_t));
	if (fork == NULL)
		return (NULL);
	pthread_mutex_init(fork, NULL);
	return (fork);
}

void	free_forks(pthread_mutex_t **forks)
{
	int	i;

	i = 0;
	while (forks[i])
	{
		pthread_mutex_destroy(forks[i]);
		free(forks[i]);
		i++;
	}
	free(forks);
}
void	free_table(t_table *table)
{
	free_forks(table->forks);
	free(table);
}

pthread_mutex_t	**init_forks(t_table *table)
{
	unsigned int	i;
	pthread_mutex_t	**forks;
	pthread_mutex_t	*fork;

	i = 0;
	forks = malloc((table->number_of_philo + 1) * sizeof(pthread_mutex_t*));
	if (forks == NULL)
		return (NULL);
	while (i < table->number_of_philo)
	{
		fork = init_fork();
		forks[i] = fork;
		i++;
	}
	forks[i] = NULL;
	return (forks);
}

t_table	*init_table(int argc, char **argv)
{
	t_table	*table;

	(void)argc;
	table = malloc(sizeof(t_table));
	table->number_of_philo = ft_atoi_ul(argv[1]);
	if (argv[5])
		table->required_eats_per_philo = ft_atoi_ul(argv[5]);
	else
		table->required_eats_per_philo = -1;
	table->forks = init_forks(table);
	table->time_at_start = get_time_in_milliescondes();
	table->end_simulation = FALSE;
	table->count_eat = 0;
	pthread_mutex_init(&table->write_access, NULL);
	pthread_mutex_init(&table->mutex_count_eat, NULL);
	return (table);
}
