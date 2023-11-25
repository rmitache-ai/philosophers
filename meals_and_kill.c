/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meals_and_kill.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 22:43:43 by rmitache          #+#    #+#             */
/*   Updated: 2023/10/28 00:38:28 by rmitache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_loop_false_kill(t_data	*data)
{
	t_phil	*philos;
	int		nb_philos;
	int		i;

	pthread_mutex_lock(&data->mut_loop);
	data->keep_loop = false;
	pthread_mutex_unlock(&data->mut_loop);
	philos = data->philos;
	nb_philos = get_nb_phil(data);
	i = -1;
	while (++i < nb_philos)
		change_state(&philos[i], DEAD);
}

void	update_meals_had(t_phil	*philo)
{
	pthread_mutex_lock(&philo->mut_nbr_of_meals);
	philo->nb_meals_had++;
	pthread_mutex_unlock(&philo->mut_nbr_of_meals);
}

bool	check_meals_had(t_data	*data, t_phil *philo)
{
	bool	res;

	if ((current_meals(philo) >= data->nbr_times_must_eat))
		res = true;
	else
		res = false;
	return (res);
}

int	current_meals(t_phil	*philo)
{
	int	res;

	pthread_mutex_lock(&philo->mut_nbr_of_meals);
	res = philo->nb_meals_had;
	pthread_mutex_unlock(&philo->mut_nbr_of_meals);
	return (res);
}
