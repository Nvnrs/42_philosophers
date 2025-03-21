/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:32:07 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/21 18:39:39 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


t_bool	check_philos_have_eaten(t_table *table)
{
	int total_eats;
	t_bool	have_eaten;

	if (table->required_eats_per_philo < 0)
		return (FALSE);
	pthread_mutex_lock(&table->mutex_count_eat);
	have_eaten = FALSE;
	total_eats = table->required_eats_per_philo * (int)table->number_of_philo;
	if (table->count_eat > total_eats)
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

void	print_message(t_action state, t_philo *philo)
{
	unsigned long current_time;

	pthread_mutex_lock(&philo->table->write_access);
	current_time = get_time_in_milliescondes() - philo->table->time_at_start;
	if (state == SLEEP)
		printf(SLEEP_MESSAGE, current_time, philo->id);
	if (state == EAT)
		printf(EAT_MESSAGE, current_time, philo->id);
	if (state == THINK)
		printf(THINK_MESSAGE, current_time, philo->id);
	if (state == FORK)
		printf(FORK_MESSAGE, current_time, philo->id);
	if (state == DEAD)
		printf(DEAD_MESSAGE, current_time, philo->id);
	pthread_mutex_unlock(&philo->table->write_access);
}

t_status	eat(t_philo *philo)
{

	// unsigned	long time;
	// time = philo->time_to_eat * 1000;
	pthread_mutex_lock(philo->fork_left);
	pthread_mutex_lock(philo->fork_right);
	philo->state = EAT;
	philo->time_last_eat = get_time_in_milliescondes();
	print_message(EAT, philo);
	if (sleep_and_check_dead(philo->time_to_eat, philo, TRUE) != THREAD_SUCCESS)
	{		
		// if (simulation_has_ended(philo->table))
		// 	return (THREAD_END);
		// if (check_philos_have_eaten(philo->table))
		// 	return (THREAD_END);
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
		return (THREAD_DEAD);
	}
	pthread_mutex_lock(&philo->table->mutex_count_eat);
	philo->table->count_eat++;
	pthread_mutex_unlock(&philo->table->mutex_count_eat);
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
	return (THREAD_SUCCESS);
}


t_status	action(unsigned long action_time, t_action action, t_philo *philo)
{
	// long time;

	// time = action_time * 1000;

	philo->state = action;
	print_message(action, philo);
	if (sleep_and_check_dead(action_time, philo, TRUE) != THREAD_SUCCESS)
	{
		// if (simulation_has_ended(philo->table))
		// 	return (THREAD_END);
		// if (check_philos_have_eaten(philo->table))
		// 	return (THREAD_END);
		return (THREAD_DEAD);
	}
		// usleep(time);
	// if (philo_is_dead(philo))
	// 	return (THREAD_DEAD);
	return (THREAD_SUCCESS);
}


void	*routine(void	*philo_void)
{
	t_philo	*philo;
	int		*status;

	philo = philo_void;
	status = malloc(sizeof(int));
	*status = THREAD_SUCCESS;
	usleep(philo->start_delay * 1000);
	philo->time_last_eat = get_time_in_milliescondes();
	while (*status == THREAD_SUCCESS)
	{
		*status = action(0, THINK, philo);
		if (*status == THREAD_SUCCESS && philo->fork_left != NULL)
			*status = action(0, FORK, philo);
		if (*status == THREAD_SUCCESS && philo->fork_right != NULL)
			*status = action(0, FORK, philo);
		if (*status == THREAD_SUCCESS &&  philo->fork_left && philo->fork_right)
			*status = eat(philo);
		if (*status == THREAD_SUCCESS &&  philo->fork_left && philo->fork_right)
			*status = action(philo->time_to_sleep, SLEEP, philo);
		
		// if (status != )
		// if (philo->fork_left == NULL || philo->fork_right == NULL)
		// 	*status = THREAD_DEAD;
	}
	return (status);
}


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

void	join_threads(t_philo **philos, t_table *table)
{
	int	i;
	int	*return_val;

	i = 0;
	while (philos[i])
	{
		pthread_join(philos[i]->thread, (void **)&return_val);
		if (*return_val == THREAD_DEAD)
		{
			printf("return VALUE %d\n", *return_val);
			pthread_mutex_lock(&table->mutex_end);
			table->end_simulation = TRUE;
			pthread_mutex_unlock(&table->mutex_end);
			print_message(DEAD, philos[i]);
		}
		free((void *)return_val);
		i++;
	}
} 

void	add_start_delay_philos(t_philo **philos)
{
	int	i;

	i = 0;
	if (len_tab((void **)philos) == 1)
		return;
	while (philos[i])
	{
		if (is_last_philo(philos, i)				
		&& len_tab((void **)philos) % 2 != 0)
		{
			philos[i]->start_delay = (philos[i]->time_to_eat * 2);
		}
		else if (i % 2 != 0)
		{
			philos[i]->start_delay = philos[i]->time_to_eat;
		}
		i++;
	}
}
