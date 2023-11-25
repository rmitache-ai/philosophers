/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines_and_joins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 22:35:51 by rmitache          #+#    #+#             */
/*   Updated: 2023/10/28 00:36:40 by rmitache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*full_check(void	*data_p)
{
	t_phil	*philo;
	t_data	*data;
	int		i;

	data = (t_data *)data_p;
	philo = data->philos;
	i = -1;
	while (++i < get_nb_phil(philo->data) && iter(data))
	{
		usleep(1000);
		if (check_meals_had(data, &philo[i]) == false)
			i = -1;
	}
	if (iter(data))
		set_loop_false_kill(data);
	return (NULL);
}

void	*routine(void *philo_data)
{
	t_phil	*philo;

	philo = (t_phil *)philo_data;
	calculate_last_eat_time(philo);
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_eat - 10);
	while (philo_state(philo) != DEAD)
	{
		if (eat(philo) != 0)
			break ;
		if (philo_state(philo) == DEAD)
			break ;
		if (philo_sleep(philo) != 0)
			break ;
		if (philo_state(philo) == DEAD)
			break ;
		if (think(philo) != 0)
			break ;
	}
	return (NULL);
}

void	*check_alive(void *data_p)
{
	t_data	*data;
	t_phil	*philo;
	int		i;
	int		nb_philos;

	data = (t_data *)data_p;
	nb_philos = get_nb_phil(data);
	philo = data->philos;
	i = -1;
	while (++i < nb_philos && iter(data))
	{
		if (philo->data->nbr_times_must_eat >= 1
			&& (check_meals_had(philo->data, philo) == true))
			return (NULL);
		if (is_dead(&philo[i]) && iter(data))
		{
			write_message(data, philo->id, RIP);
			set_loop_false_kill(data);
			break ;
		}
		if (i == (nb_philos - 1))
			i = -1;
		usleep(1000);
	}
	return (NULL);
}

int	start_threads(t_data *data)
{
	int		nb_philos;
	int		i;

	i = -1;
	data->time_start = get_time();
	nb_philos = get_nb_phil(data);
	while (++i < nb_philos)
	{
		if (pthread_create(&data->philo_thread[i], NULL,
				&routine, &data->philos[i]))
			return (1);
	}
	if (pthread_create(&data->philos_alive_thread, NULL, &check_alive, data))
		return (1);
	if ((data->nbr_times_must_eat >= 1)
		&& pthread_create(&data->philos_meals_thread, NULL, &full_check, data))
		return (1);
	if (!join_them_threads(data))
		return (1);
	return (0);
}

int	join_them_threads( t_data *data)
{
	int	i;
	int	nb_philos;

	i = -1;
	nb_philos = get_nb_phil(data);
	if (pthread_join(data->philos_alive_thread, NULL))
		return (1);
	if ((data->nbr_times_must_eat >= 1)
		&& pthread_join(data->philos_meals_thread, NULL))
		return (1);
	while (++i < nb_philos)
	{
		if (pthread_join(data->philo_thread[i], NULL))
			return (1);
	}
	return (0);
}
