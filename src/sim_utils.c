/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsarkoh <fsarkoh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:42:09 by fsarkoh           #+#    #+#             */
/*   Updated: 2023/05/03 14:55:18 by fsarkoh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned int	is_sim_running(t_sim *sim)
{
	unsigned int	is_running;

	pthread_mutex_lock(sim->sync_mutex);
	is_running = sim->is_running;
	pthread_mutex_unlock(sim->sync_mutex);
	return (is_running);
}

unsigned int	should_sim_stop(t_sim *sim)
{
	unsigned int	should_sim_stop;

	pthread_mutex_lock(sim->sync_mutex);
	should_sim_stop = sim->should_stop;
	pthread_mutex_unlock(sim->sync_mutex);
	return (should_sim_stop);
}
