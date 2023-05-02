/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philosophers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joel <joel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 11:12:50 by joel              #+#    #+#             */
/*   Updated: 2023/05/02 22:15:12 by joel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include <stdlib.h>
#include "philo.h"

static int	create_philo_thread(t_thread *thread_id,
	t_philosopher *philosopher, t_sim *sim)
{
	t_thread_arg	*thread_arg;

	thread_arg = (t_thread_arg *)malloc(sizeof(t_thread_arg));
	if (!thread_arg)
		return (ERROR);
	thread_arg->philosopher = philosopher;
	thread_arg->sim = sim;
	return (pthread_create(thread_id, NULL,
			philo_main, (void *)thread_arg));
}

static void	init_data(unsigned int id, t_philosopher *philosopher, t_sim *sim)
{
	philosopher->id = id;
	philosopher->n_meals = 0;
	philosopher->last_meal = 0;
	philosopher->is_finished = FALSE;
	philosopher->right_fork = *(sim->forks + id - 1);
	if (id > 1)
		philosopher->left_fork = *(sim->forks + id - 2);
	else
		philosopher->left_fork = *(sim->forks + sim->n_philo - 1);
}

static t_philosopher	*init_philosopher(unsigned int id, t_sim *sim)
{
	t_philosopher	*philosopher;
	t_thread		thread_id;

	philosopher = (t_philosopher *)malloc(sizeof(t_philosopher));
	if (!philosopher)
		return (NULL);
	philosopher->philo_mutex = (t_mutex *)malloc(sizeof(t_mutex));
	if (!philosopher->philo_mutex)
	{
		free(philosopher);
		return (NULL);
	}
	if (create_philo_thread(&thread_id, philosopher, sim))
	{
		free(philosopher);
		return (NULL);
	}
	philosopher->thread_id = thread_id;
	pthread_mutex_lock(sim->sync_mutex);
	init_data(id, philosopher, sim);
	pthread_mutex_unlock(sim->sync_mutex);
	return (philosopher);
}

void	free_philosophers(t_philosopher **philosophers,
	unsigned int n_philo)
{
	unsigned int	cidx;

	cidx = 0;
	while (cidx < n_philo)
	{
		free(*(philosophers + cidx));
		cidx++;
	}
}

t_philosopher	**init_philosophers(t_sim *sim)
{
	unsigned int	cidx;
	t_philosopher	**philosophers;
	t_philosopher	*current_philosopher;

	cidx = 0;
	philosophers
		= (t_philosopher **)malloc(sizeof(t_philosopher *) * sim->n_philo);
	if (!philosophers)
		return (NULL);
	while (cidx < sim->n_philo)
	{
		current_philosopher = init_philosopher(cidx + 1, sim);
		if (!current_philosopher)
		{
			free_philosophers(philosophers, cidx);
			free(philosophers);
			return (NULL);
		}
		*(philosophers + cidx) = current_philosopher;
		cidx++;
	}
	return (philosophers);
}
