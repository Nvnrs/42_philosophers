/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:17:44 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/17 17:27:40 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_format_input()
{
	ft_putstr_fd("The programm needs :\n", 2);
	ft_putstr_fd("--> 1 : number of philosophers\n", 2);
	ft_putstr_fd("--> 2 : time to die\n", 2);
	ft_putstr_fd("--> 3 : time to eat\n", 2);
	ft_putstr_fd("--> 4 : time to sleep\n", 2);
	ft_putstr_fd("--> (optionnal) 5 : number of times each philosopher must eat\n", 2);
	ft_putstr_fd("Please check and try again\n", 2);
}

t_bool	all_args_are_valid(char **argv)
{
	int i;

	i = 0;
	while (argv[i])
	{
		if (!is_valid_number(argv[i]))
			return (ft_putstr_fd("Only positive number are accepted\n", 2), FALSE);
		if (!is_in_range_of_unsigned_int(argv[i]))
			return (ft_putstr_fd("The number must be define between 0 and 4294967295\n", 2), FALSE);
		i++;
	}
	return (TRUE);
}

t_bool	check_input(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (error_format_input(), FALSE);
	if (!all_args_are_valid(&argv[1]))
		return (FALSE);
	return (TRUE);
}