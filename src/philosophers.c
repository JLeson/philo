/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joel <joel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 11:17:19 by joel              #+#    #+#             */
/*   Updated: 2023/04/28 17:32:35 by joel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "colorcodes.h"
#include "philo.h"

unsigned int	is_meal_quota_met(t_sim *sim)
{
	unsigned int	cidx;
	t_philosopher	*philosopher;

	cidx = 0;
	if (sim->n_meals == 0)
		return (FALSE);
	while (cidx < sim->n_philo)
	{
		pthread_mutex_lock(sim->meal_mutex);
		philosopher = *(sim->philosophers + cidx);
		if (philosopher->n_meals < sim->n_meals)
		{
			pthread_mutex_unlock(sim->meal_mutex);
			return (FALSE);
		}
		else
			pthread_mutex_unlock(sim->meal_mutex);
		cidx++;
	}
	return (TRUE);
}

static void	philo_eat(t_philosopher *philosopher, t_sim *sim)
{
	pthread_mutex_lock(philosopher->right_fork);
	log_msg(philosopher->id, CC_BLUE"has taken a fork"CC_OFF, sim);
	pthread_mutex_lock(philosopher->left_fork);
	log_msg(philosopher->id, CC_BLUE"has taken a fork"CC_OFF, sim);
	log_state(philosopher->id, EAT, sim);
	pthread_mutex_lock(sim->meal_mutex);
	philosopher->last_meal = get_timestamp(sim->time_start);
	pthread_mutex_unlock(sim->meal_mutex);
	precise_usleep(sim->time_eat);
	philosopher->n_meals += 1;
	pthread_mutex_unlock(philosopher->left_fork);
	pthread_mutex_unlock(philosopher->right_fork);
}

void	*philo_main(void *arg)
{
	t_thread_arg	*thread_arg;
	t_sim			*sim;
	t_philosopher	*philosopher;

	thread_arg = (t_thread_arg *)arg;
	while (TRUE)
	{
		pthread_mutex_lock(thread_arg->sim->sync_mutex);
		if (thread_arg->sim->is_running)
		{
			pthread_mutex_unlock(thread_arg->sim->sync_mutex);
			break ;
		}
		pthread_mutex_unlock(thread_arg->sim->sync_mutex);
	}
	sim = thread_arg->sim;
	philosopher = thread_arg->philosopher;
	if (philosopher->id % 2)
	{
		log_state(philosopher->id, THINK, sim);
		precise_usleep(sim->time_eat);
	}
	while (TRUE)
	{
		philo_eat(philosopher, sim);
		if (sim->should_stop || is_meal_quota_met(sim))
		{
			sim->should_stop = TRUE;
			return (NULL);
		}
		log_state(philosopher->id, SLEEP, sim);
		precise_usleep(sim->time_sleep);
		log_state(philosopher->id, THINK, sim);
	}
	return (NULL);
}
