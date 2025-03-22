/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_ul.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:16:40 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/22 14:09:38 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	get_digit_position(unsigned long nb, int position)
{
	unsigned long	output;

	output = nb;
	while (position >= 1)
	{
		output *= 10;
		position--;
	}
	return (output);
}

unsigned long	ft_atoi_ul(char *str)
{
	int				i;
	unsigned long	nb;
	int				position_digit;

	i = 0;
	nb = 0;
	if (str[i] == '+')
		i++;
	position_digit = ft_strlen(&str[i]) - 1;
	while (str[i])
	{
		nb += get_digit_position(str[i] - '0', position_digit);
		position_digit--;
		i++;
	}
	return (nb);
}
