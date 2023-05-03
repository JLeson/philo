/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsarkoh <fsarkoh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 14:49:47 by joel              #+#    #+#             */
/*   Updated: 2023/05/03 15:03:38 by fsarkoh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include <stdlib.h>
#include "philo.h"

void	start_sim(t_sim *sim)
{
	pthread_mutex_lock(sim->sync_mutex);
	sim->is_running = TRUE;
	sim->time_start = get_time();
	pthread_mutex_unlock(sim->sync_mutex);
}

void	stop_sim(t_sim *sim)
{
	pthread_mutex_lock(sim->sync_mutex);
	sim->is_running = FALSE;
	pthread_mutex_unlock(sim->sync_mutex);
}

void	clean_sim(t_sim *sim)
{
	unsigned int	cidx;

	cidx = 0;
	while (cidx < sim->n_philo)
	{
		pthread_mutex_destroy(*(sim->forks + cidx));
		free(*(sim->philosophers + cidx));
		free(*(sim->forks + cidx));
		cidx++;
	}
	pthread_mutex_destroy(sim->sync_mutex);
	pthread_mutex_destroy(sim->log_mutex);
	free(sim->philosophers);
	free(sim->forks);
}

void	wait_for_threads(t_sim *sim)
{
	unsigned int	cidx;
	t_philosopher	*philosopher;

	cidx = 0;
	while (cidx < sim->n_philo)
	{
		philosopher = *(sim->philosophers + cidx);
		pthread_join(philosopher->thread_id, NULL);
		cidx++;
	}
}
