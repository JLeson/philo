/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsarkoh <fsarkoh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:50:17 by joel              #+#    #+#             */
/*   Updated: 2023/05/03 15:44:45 by fsarkoh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "colorcodes.h"
#include "philo.h"

static int	is_valid(int argc, char **argv)
{	
	unsigned int	cidx;

	if (argc < 5 || argc > 6)
		return (FALSE);
	if (ft_atoi(*(argv + 1)) == 0)
		return (FALSE);
	cidx = 1;
	while (cidx < (unsigned int)argc)
	{
		if (!is_num(*(argv + cidx)))
			return (FALSE);
		if (!is_int32(*(argv + cidx)))
			return (FALSE);
		cidx++;
	}
	return (TRUE);
}

int	main(int argc, char **argv)
{
	t_sim	sim;
	t_mutex	sync_mutex;
	t_mutex	log_mutex;

	if (!is_valid(argc, argv))
		return (ERROR);
	if (pthread_mutex_init(&sync_mutex, NULL))
		return (ERROR);
	if (pthread_mutex_init(&log_mutex, NULL))
		return (ERROR);
	sim.argc = argc;
	sim.sync_mutex = &sync_mutex;
	sim.log_mutex = &log_mutex;
	if (init_sim(&sim, argc, argv))
		return (ERROR);
	start_sim(&sim);
	if (sim.argc == 6 && sim.n_meals == 0)
		stop_sim(&sim);
	while (sim.is_running)
		monitor(&sim);
	clean_sim(&sim);
	return (SUCCES);
}
