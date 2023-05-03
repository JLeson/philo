/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsarkoh <fsarkoh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:52:44 by fsarkoh           #+#    #+#             */
/*   Updated: 2023/05/03 16:38:21 by fsarkoh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "philo.h"

static unsigned int	is_meal_quota_met(t_sim *sim)
{
	t_philosopher	*philosopher;
	unsigned int	cidx;

	cidx = 0;
	while (cidx < sim->n_philo)
	{
		philosopher = *(sim->philosophers + cidx);
		pthread_mutex_lock(philosopher->philo_mutex);
		if (!philosopher->is_finished)
		{
			pthread_mutex_unlock(philosopher->philo_mutex);
			return (FALSE);
		}
		else
			pthread_mutex_unlock(philosopher->philo_mutex);
		cidx++;
	}
	return (TRUE);
}

static unsigned int	philo_has_starved(t_sim *sim)
{
	unsigned int	cidx;
	t_philosopher	*philosopher;

	cidx = 0;
	while (cidx < sim->n_philo)
	{
		philosopher = *(sim->philosophers + cidx);
		pthread_mutex_lock(philosopher->philo_mutex);
		if (get_timestamp(sim->time_start) - philosopher->last_meal
			> sim->time_die)
		{
			pthread_mutex_unlock(philosopher->philo_mutex);
			log_state(philosopher->id, DIE, sim);
			return (TRUE);
		}
		else
			pthread_mutex_unlock(philosopher->philo_mutex);
		cidx++;
	}
	return (FALSE);
}

void	monitor(t_sim *sim)
{
	if (philo_has_starved(sim) || is_meal_quota_met(sim))
	{
		pthread_mutex_lock(sim->sync_mutex);
		sim->should_stop = TRUE;
		pthread_mutex_unlock(sim->sync_mutex);
		wait_for_threads(sim);
		stop_sim(sim);
	}
}
