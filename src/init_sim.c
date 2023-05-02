/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joel <joel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 11:02:42 by joel              #+#    #+#             */
/*   Updated: 2023/04/28 14:48:53 by joel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "philo.h"

int	init_sim(t_sim *sim, int argc, char **argv)
{
	sim->n_philo = ft_atoi(*(argv + 1));
	if (sim->n_philo > MAX_PHILO)
		return (ERROR);
	sim->time_die = ft_atoi(*(argv + 2));
	sim->time_eat = ft_atoi(*(argv + 3));
	sim->time_sleep = ft_atoi(*(argv + 4));
	sim->n_meals = 0;
	if (argc == 6)
		sim->n_meals = ft_atoi(*(argv + 5));
	sim->is_running = FALSE;
	sim->should_stop = FALSE;
	sim->forks = init_forks(sim->n_philo);
	if (!(sim->forks))
		return (ERROR);
	sim->philosophers = init_philosophers(sim);
	if (!(sim->philosophers))
	{
		free_forks(sim->forks, sim->n_philo);
		free(sim->forks);
		return (ERROR);
	}
	return (SUCCES);
}
