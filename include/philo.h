/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsarkoh <fsarkoh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:47:47 by joel              #+#    #+#             */
/*   Updated: 2023/05/03 15:37:03 by fsarkoh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

# define INT_MAX	2147483647

# define MAX_PHILO	200

# define TRUE    1
# define FALSE   0

# define ERROR   1
# define SUCCES  0

# define THINK   0
# define EAT     1
# define SLEEP   2
# define DIE     3

typedef pthread_mutex_t			t_mutex;
typedef pthread_t				t_thread;
typedef struct s_sim			t_sim;
typedef struct s_philosopher	t_philosopher;
typedef struct s_fork			t_fork;
typedef struct s_thread_arg		t_thread_arg;
typedef long long				t_msec;

typedef struct s_sim
{
	unsigned int	n_philo;
	t_msec			time_die;
	t_msec			time_eat;
	t_msec			time_sleep;
	unsigned int	n_meals;
	t_msec			time_start;
	unsigned int	is_running;
	unsigned int	should_stop;
	t_philosopher	**philosophers;
	t_mutex			**forks;
	t_mutex			*log_mutex;
	t_mutex			*sync_mutex;
	int				argc;
}	t_sim;

typedef struct s_philosopher
{
	unsigned int	id;
	t_thread		thread_id;
	t_mutex			*right_fork;
	t_mutex			*left_fork;
	t_mutex			*philo_mutex;
	unsigned int	n_meals;
	t_msec			last_meal;
	unsigned int	is_finished;
}	t_philosopher;

typedef struct s_thread_arg
{
	t_philosopher	*philosopher;
	t_sim			*sim;
}	t_thread_arg;

//	init_sim.c

int				init_sim(t_sim *sim, int argc, char **argv);

//	init_forks.c

void			free_forks(t_mutex **forks, unsigned int n_forks);
t_mutex			**init_forks(unsigned int n_philo);

//	init_philosopher.c

void			free_philosophers(t_philosopher **philosophers,
					unsigned int n_philo);
t_philosopher	**init_philosophers(t_sim *sim);

//	validation.c

unsigned int	is_num(char *arg);
unsigned int	is_int32(char *arg);

//	sim.c

void			start_sim(t_sim *sim);
void			stop_sim(t_sim *sim);
void			clean_sim(t_sim *sim);
void			wait_for_threads(t_sim *sim);

//	sim_utils.c

unsigned int	is_sim_running(t_sim *sim);
unsigned int	should_sim_stop(t_sim *sim);

//	monitor.c

void			monitor(t_sim *sim);

//	philosopher.c

void			*philo_main(void *arg);

//	log.c

void			log_state(unsigned int id, unsigned int state, t_sim *sim);
void			log_msg(unsigned int id, const char *msg, t_sim *sim);

//	time.c

t_msec			get_time(void);
t_msec			get_timestamp(t_msec time_start);

//	utils.c

unsigned int	ft_isdigit(int c);
unsigned int	ft_isspace(const char c);
int				ft_atoi(const char *str);
void			precise_usleep(t_msec msec);
#endif