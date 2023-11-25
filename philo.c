/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 18:22:06 by rmitache          #+#    #+#             */
/*   Updated: 2023/11/15 18:33:42 by rmitache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_nb_phil(t_data *data)
{
	int	nb_philos;

	pthread_mutex_lock(&data->mut_nbr_philos);
	nb_philos = data->nbr_philos;
	pthread_mutex_unlock(&data->mut_nbr_philos);
	return (nb_philos);
}

uint64_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

bool	is_dead(t_phil	*philo)
{
	bool	dead;
	t_data	*data;

	dead = false;
	data = philo->data;
	if (((get_time() - get_last_eat_time(philo)) > get_die_time(data))
		&& philo_state(philo) != EATING)
	{
		change_state(philo, DEAD);
		dead = true;
	}
	return (dead);
}

void	calculate_last_eat_time(t_phil *philo)
{
	pthread_mutex_lock(&philo->mut_last_eat_time);
	philo->last_eat_time = get_time();
	pthread_mutex_unlock(&philo->mut_last_eat_time);
}

int	main(int argc, char **argv)
{
	if (check_arguments(argc, argv))
		print_instructions();
	else
	{
		if (start_process(argc, argv) == MALLOC_ERROR)
			return (MALLOC_ERROR);
	}
	return (0);
}
