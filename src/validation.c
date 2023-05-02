/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joel <joel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:54:44 by joel              #+#    #+#             */
/*   Updated: 2023/04/28 10:54:48 by joel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned int	is_num(char *arg)
{
	unsigned int	offset;

	offset = 0;
	while (ft_isspace(*(arg + offset)))
		offset++;
	while (*(arg + offset))
	{	
		if (!ft_isdigit(*(arg + offset)))
			return (FALSE);
		offset++;
	}
	return (TRUE);
}

unsigned int	is_int32(char *arg)
{
	unsigned long long int	to;
	int						offset;

	offset = 0;
	to = 0;
	while (*(arg + offset))
	{
		to = to * 10 + (*(arg + offset) - '0');
		offset++;
	}
	if (to > INT_MAX)
		return (FALSE);
	return (TRUE);
}
