/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joel <joel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 14:49:47 by joel              #+#    #+#             */
/*   Updated: 2023/04/28 15:26:43 by joel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	pthread_mutex_destroy(sim->meal_mutex);
	sim->is_running = FALSE;
}

static void	wait_for_threads(t_sim *sim)
{
	unsigned int	cidx;
	t_philosopher	*philosopher;

	cidx = 0;
	while (sim->n_philo < cidx)
	{
		philosopher = *(sim->philosophers + cidx);
		pthread_join(philosopher->thread_id, NULL);
		cidx++;
	}
}

void	check_starvation(t_sim *sim)
{
	unsigned int	cidx;
	t_philosopher	*philosopher;

	cidx = 0;
	while (cidx < sim->n_philo)
	{
		philosopher = *(sim->philosophers + cidx);
		pthread_mutex_lock(sim->meal_mutex);
		if (get_timestamp(sim->time_start) - philosopher->last_meal
			> sim->time_die)
		{
			pthread_mutex_unlock(sim->meal_mutex);
			log_state(philosopher->id, DIE, sim);
			sim->should_stop = TRUE;
			wait_for_threads(sim);
			stop_sim(sim);
			return ;
		}
		else
			pthread_mutex_unlock(sim->meal_mutex);
		cidx++;
	}
}
