/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joel <joel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 11:09:07 by joel              #+#    #+#             */
/*   Updated: 2023/04/28 11:09:09 by joel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "philo.h"

void	free_forks(t_mutex **forks, unsigned int n_forks)
{
	unsigned int	cidx;

	cidx = 0;
	while (cidx < n_forks)
	{
		free(*(forks + cidx));
		cidx++;
	}
}

static t_mutex	*init_fork(void)
{
	t_mutex	*fork;

	fork = (t_mutex *)malloc(sizeof(t_mutex));
	if (!fork)
		return (NULL);
	pthread_mutex_init(fork, NULL);
	return (fork);
}

t_mutex	**init_forks(unsigned int n_philo)
{
	unsigned int	cidx;
	t_mutex			**forks;
	t_mutex			*current_fork;

	forks = (t_mutex **)malloc(sizeof(t_mutex) * n_philo);
	if (!forks)
		return (NULL);
	cidx = 0;
	while (cidx < n_philo)
	{
		current_fork = init_fork();
		if (!current_fork)
		{
			free_forks(forks, cidx);
			free(forks);
			return (NULL);
		}
		*(forks + cidx) = current_fork;
		cidx++;
	}
	return (forks);
}
