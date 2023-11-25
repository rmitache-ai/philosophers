/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 14:51:06 by rmitache          #+#    #+#             */
/*   Updated: 2023/10/27 23:25:52 by rmitache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdint.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdbool.h>

# define MALLOC_ERROR -2

# define TAKEN_FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define RIP "died"
# define RED "\x1B[31m"
# define GREEN "\x1B[32m"
# define YELLOW "\x1B[33m"
# define RESET "\x1B[0m"
# define LIGHT_BLUE "\x1B[94m"

typedef enum e_phil_state
{
	EATING = 0,
	ATE = 1,
	SLEEPING = 2,
	THINKING = 3,
	DEAD = 4,
	DEFAULT = 5
}	t_state;

typedef struct s_phil
{
	int				id;
	int				nb_meals_had;
	uint64_t		last_eat_time;
	struct s_data	*data;
	t_state			state;
	pthread_mutex_t	*left_f;
	pthread_mutex_t	*right_f;
	pthread_mutex_t	mut_state;
	pthread_mutex_t	mut_nbr_of_meals;
	pthread_mutex_t	mut_last_eat_time;
}	t_phil;

typedef struct s_data
{
	int				nbr_philos;
	int				nbr_times_must_eat;
	bool			keep_loop;
	uint64_t		time_die;
	uint64_t		time_start;
	uint64_t		time_eat;
	uint64_t		time_sleep;
	pthread_mutex_t	*forks;
	pthread_mutex_t	mut_loop;
	pthread_mutex_t	mut_time_start;
	pthread_mutex_t	mut_time_eat;
	pthread_mutex_t	mut_time_die;
	pthread_mutex_t	mut_nbr_philos;
	pthread_mutex_t	mut_str;
	pthread_mutex_t	mut_time_sleep;
	pthread_t		philos_alive_thread;
	pthread_t		philos_meals_thread;
	pthread_t		*philo_thread;
	t_phil			*philos;
}	t_data;

// Get Information
uint64_t	get_last_eat_time(t_phil *philo);
uint64_t	get_eat_time(t_data *data);
uint64_t	get_sleep_time(t_data *data);
uint64_t	get_die_time(t_data *data);
t_state		philo_state(t_phil *philo);

// Get more information
int			get_nb_phil(t_data *data);
uint64_t	get_time(void);
bool		is_dead(t_phil *philo);
void		calculate_last_eat_time(t_phil *philo);

// Routines & Joins
void		*full_check(void *data_p);
void		*routine(void *philo_data);
void		*check_alive(void *data_p);
int			start_threads(t_data *data);
int			join_them_threads(t_data *data);

// Init & Change State
int			init_data(t_data *data, int argc, char **argv);
void		init_philo(t_data *data);
void		init_forks(t_data *data);
int			take_forks(t_phil *philo);
void		change_state(t_phil *philo, t_state state);

// Actions
int			eat(t_phil *philo);
int			philo_sleep(t_phil *philo);
int			think(t_phil *philo);
int			take_right_fork(t_phil *philo);
int			take_left_fork(t_phil *philo);

// Utils
int			ft_atoi(const char *str);
void		free_data(t_data *data);
int			iter(t_data *data);
void		write_message(t_data *data, int id, char *str);
void		print_instructions(void);

// Meals & Kill
void		update_meals_had(t_phil *philo);
bool		check_meals_had(t_data *data, t_phil *philo);
int			current_meals(t_phil	*philo);
void		set_loop_false_kill(t_data	*data);

// Parsing & others
int			check_arguments(int argc, char **argv);
int			handle_1_philo(t_phil *philo);
int			start_process(int argc, char **argv);
int			ft_usleep(uint64_t sleep_time);
uint64_t	start_time(t_data *data);

#endif