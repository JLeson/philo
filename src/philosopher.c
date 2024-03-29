/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsarkoh <fsarkoh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 11:17:19 by joel              #+#    #+#             */
/*   Updated: 2023/05/03 18:30:56 by fsarkoh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "colorcodes.h"
#include "philo.h"

static void	philo_eat(t_philosopher *philosopher, t_sim *sim)
{
	pthread_mutex_lock(philosopher->right_fork);
	log_msg(philosopher->id, CC_BLUE"has taken a fork"CC_OFF, sim);
	pthread_mutex_lock(philosopher->left_fork);
	log_msg(philosopher->id, CC_BLUE"has taken a fork"CC_OFF, sim);
	pthread_mutex_lock(philosopher->philo_mutex);
	philosopher->last_meal = get_timestamp(sim->time_start);
	pthread_mutex_unlock(philosopher->philo_mutex);
	log_state(philosopher->id, EAT, sim);
	philosopher->n_meals += 1;
	precise_usleep(sim->time_eat);
	pthread_mutex_unlock(philosopher->left_fork);
	pthread_mutex_unlock(philosopher->right_fork);
}

static void	philo_routine(t_philosopher *philosopher, t_sim *sim)
{
	if (sim->n_philo == 1)
		return ;
	if (philosopher->id % 2)
		precise_usleep(sim->time_eat);
	while (!should_sim_stop(sim))
	{
		philo_eat(philosopher, sim);
		if (philosopher->n_meals == sim->n_meals)
		{
			pthread_mutex_lock(philosopher->philo_mutex);
			philosopher->is_finished = TRUE;
			pthread_mutex_unlock(philosopher->philo_mutex);
		}
		log_state(philosopher->id, SLEEP, sim);
		precise_usleep(sim->time_sleep);
		log_state(philosopher->id, THINK, sim);
	}
}

void	*philo_main(void *arg)
{
	t_thread_arg	*thread_arg;
	t_sim			*sim;
	t_philosopher	*philosopher;

	thread_arg = (t_thread_arg *)arg;
	if (thread_arg->sim->argc == 6 && thread_arg->sim->n_meals == 0)
		return (NULL);
	while (!is_sim_running(thread_arg->sim))
		;
	sim = thread_arg->sim;
	philosopher = thread_arg->philosopher;
	philo_routine(philosopher, sim);
	free(thread_arg);
	return (NULL);
}
