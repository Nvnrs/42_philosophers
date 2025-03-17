/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_number.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:20:23 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/17 17:22:00 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+')
		i++;
	if(str[i] == '\0')
		return (FALSE);
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

t_bool	is_in_range_of_unsigned_int(char *str)
{
	unsigned long nb;

	nb = ft_atoi_ul(str);
	if (nb > MAX_UI)
		return (FALSE);
	return (TRUE);
}