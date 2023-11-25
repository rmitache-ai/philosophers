/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 18:20:29 by rmitache          #+#    #+#             */
/*   Updated: 2023/10/26 16:41:04 by rmitache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	get_last_eat_time(t_phil *philo)
{
	uint64_t	time;

	pthread_mutex_lock(&philo->mut_last_eat_time);
	time = philo->last_eat_time;
	pthread_mutex_unlock(&philo->mut_last_eat_time);
	return (time);
}

uint64_t	get_eat_time(t_data *data)
{
	uint64_t	time;

	pthread_mutex_lock(&data->mut_time_eat);
	time = data->time_eat;
	pthread_mutex_unlock(&data->mut_time_eat);
	return (time);
}

uint64_t	get_sleep_time(t_data *data)
{
	uint64_t	time;

	pthread_mutex_lock(&data->mut_time_sleep);
	time = data->time_sleep;
	pthread_mutex_unlock(&data->mut_time_sleep);
	return (time);
}

uint64_t	get_die_time(t_data *data)
{
	uint64_t	time;

	pthread_mutex_lock(&data->mut_time_die);
	time = data->time_die;
	pthread_mutex_unlock(&data->mut_time_die);
	return (time);
}

t_state	philo_state(t_phil	*philo)
{
	int	state;

	pthread_mutex_lock(&philo->mut_state);
	state = philo->state;
	pthread_mutex_unlock(&philo->mut_state);
	return (state);
}
