/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_state.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 22:40:36 by rmitache          #+#    #+#             */
/*   Updated: 2023/10/28 00:37:33 by rmitache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data	*data, int argc, char **argv)
{
	data->keep_loop = true;
	data->nbr_philos = ft_atoi(argv[1]);
	data->time_die = (uint64_t) ft_atoi(argv[2]);
	data->time_eat = (uint64_t) ft_atoi(argv[3]);
	data->time_sleep = (uint64_t) ft_atoi(argv[4]);
	data->nbr_times_must_eat = 0;
	if (argc == 6)
		data->nbr_times_must_eat = ft_atoi(argv[5]);
	pthread_mutex_init(&data->mut_loop, NULL);
	pthread_mutex_init(&data->mut_time_start, NULL);
	pthread_mutex_init(&data->mut_nbr_philos, NULL);
	pthread_mutex_init(&data->mut_str, NULL);
	pthread_mutex_init(&data->mut_time_eat, NULL);
	pthread_mutex_init(&data->mut_time_sleep, NULL);
	pthread_mutex_init(&data->mut_time_die, NULL);
	data->philos = malloc(sizeof(t_phil) * data->nbr_philos);
	if (!data->philos)
		return (MALLOC_ERROR);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nbr_philos);
	if (!data->forks)
		return (free(data->philos), MALLOC_ERROR);
	data->philo_thread = malloc(sizeof(pthread_t) * data->nbr_philos);
	if (!data->philo_thread)
		return (free(data->philos), free(data->forks), MALLOC_ERROR);
	return (0);
}

void	init_philo(t_data	*data)
{
	int		i;
	t_phil	*philos;

	i = -1;
	philos = data->philos;
	while (++i < data->nbr_philos)
	{
		philos[i].data = data;
		philos[i].nb_meals_had = 0;
		philos[i].state = DEFAULT;
		philos[i].id = i + 1;
		pthread_mutex_init(&philos[i].mut_state, NULL);
		pthread_mutex_init(&philos[i].mut_nbr_of_meals, NULL);
		pthread_mutex_init(&philos[i].mut_last_eat_time, NULL);
		calculate_last_eat_time(&philos[i]);
	}
}

void	init_forks(t_data	*data)
{
	int		i;
	int		nb_philos;
	t_phil	*philos;

	i = -1;
	philos = data->philos;
	nb_philos = get_nb_phil(data);
	while (++i < nb_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		philos[i].left_f = &data->forks[i];
		philos[i].right_f = &data->forks[(i + 1) % nb_philos];
	}
}

int	take_forks(t_phil	*philo)
{
	if (get_nb_phil(philo->data) == 1)
		handle_1_philo(philo);
	if (philo->id % 2 == 0)
	{
		if (take_right_fork(philo) != 0)
			return (1);
		if (take_left_fork(philo) != 0)
		{
			pthread_mutex_unlock(philo->right_f);
			return (1);
		}
	}
	else
	{
		if (take_left_fork(philo) != 0)
			return (1);
		if (take_right_fork(philo) != 0)
		{
			pthread_mutex_unlock(philo->left_f);
			return (1);
		}
	}
	return (0);
}

void	change_state(t_phil *philo, t_state state)
{
	pthread_mutex_lock(&philo->mut_state);
	if (philo->state != DEAD)
		philo->state = state;
	pthread_mutex_unlock(&philo->mut_state);
}
