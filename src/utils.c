/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joel <joel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:52:56 by joel              #+#    #+#             */
/*   Updated: 2023/04/28 12:27:44 by joel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philo.h"

unsigned int	ft_isspace(const char c)
{
	if (c == ' ' || c == '\n' || c == '\t'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

unsigned int	ft_isdigit(int c)
{
	if (!(c >= '0' && c <= '9'))
		return (0);
	return (1);
}

int	ft_atoi(const char *str)
{
	unsigned int	offset;
	int				to;
	int				sign;

	offset = 0;
	to = 0;
	sign = 1;
	while (ft_isspace(*(str + offset)))
		offset++;
	if (*(str + offset) == '-')
	{
		sign = -1;
		offset++;
	}
	else if (*(str + offset) == '+')
		offset++;
	while (*(str + offset) == '0')
		offset++;
	while (ft_isdigit(*(str + offset)))
	{
		to *= 10;
		to += *(str + offset) - 48;
		offset++;
	}		
	return (to * sign);
}

void	precise_usleep(t_msec msec)
{
	t_msec	time;

	time = get_time();
	while (get_time() - time < msec)
		usleep(msec / 10);
}
