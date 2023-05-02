/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsarkoh <fsarkoh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 11:48:47 by joel              #+#    #+#             */
/*   Updated: 2023/05/02 14:30:44 by fsarkoh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "colorcodes.h"
#include "philo.h"

void	log_msg(unsigned int id, const char *msg, t_sim *sim)
{
	pthread_mutex_lock(sim->log_mutex);
	if (!sim->should_stop)
		printf(CC_YELLOW"%lld "CC_OFF"%u "CC_BOLD"%s\n"CC_OFF,
			get_timestamp(sim->time_start), id, msg);
	pthread_mutex_unlock(sim->log_mutex);
}

void	log_state(unsigned int id, unsigned int state, t_sim *sim)
{
	if (state == THINK)
		log_msg(id, CC_CYAN"is thinking"CC_OFF, sim);
	else if (state == SLEEP)
		log_msg(id, CC_MAGENTA"is sleeping"CC_OFF, sim);
	else if (state == EAT)
		log_msg(id, CC_GREEN"is eating"CC_OFF, sim);
	else if (state == DIE)
		log_msg(id, CC_RED"died"CC_OFF, sim);
}
