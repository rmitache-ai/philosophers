/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 22:41:38 by rmitache          #+#    #+#             */
/*   Updated: 2023/10/28 03:36:12 by rmitache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eat(t_phil *philo)
{
	if (philo->data->nbr_times_must_eat >= 1)
		if (check_meals_had(philo->data, philo) == true)
			return (1);
	if (take_forks(philo) != 0)
		return (1);
	change_state(philo, EATING);
	write_message(philo->data, philo->id, EAT);
	calculate_last_eat_time(philo);
	ft_usleep(get_eat_time(philo->data));
	update_meals_had(philo);
	pthread_mutex_unlock(philo->right_f);
	pthread_mutex_unlock(philo->left_f);
	return (0);
}

int	philo_sleep(t_phil *philo)
{
	change_state(philo, SLEEPING);
	if (philo_state(philo) == DEAD)
		return (1);
	write_message(philo->data, philo->id, SLEEP);
	ft_usleep(get_sleep_time(philo->data));
	return (0);
}

int	think(t_phil	*philo)
{
	change_state(philo, THINKING);
	if (philo_state(philo) == DEAD)
		return (1);
	write_message(philo->data, philo->id, THINK);
	return (0);
}

int	take_left_fork(t_phil *philo)
{
	if (philo_state(philo) == DEAD || is_dead(philo))
		return (1);
	pthread_mutex_lock(philo->left_f);
	write_message(philo->data, philo->id, TAKEN_FORK);
	return (0);
}

int	take_right_fork(t_phil	*philo)
{
	if (philo_state(philo) == DEAD || is_dead(philo))
		return (1);
	pthread_mutex_lock(philo->right_f);
	write_message(philo->data, philo->id, TAKEN_FORK);
	return (0);
}
