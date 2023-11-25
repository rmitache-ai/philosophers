/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_and_other.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 22:44:52 by rmitache          #+#    #+#             */
/*   Updated: 2023/10/28 00:36:38 by rmitache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_arguments(int argc, char **argv)
{
	int	i;
	int	c;

	i = 0;
	if (argc == 5 || argc == 6)
	{
		if ((argc == 6 && ft_atoi(argv[5]) < 1) || ft_atoi(argv[1]) > 200
			|| ft_atoi(argv[2]) < 60)
			return (1);
		if (ft_atoi(argv[3]) < 60 || ft_atoi(argv[4]) < 60)
			return (1);
		while (argv[++i])
		{
			c = 0;
			while (argv[i][c] != '\0')
			{
				if (!(argv[i][c] >= '0' && argv[i][c] <= '9'))
					return (1);
				c++;
			}
		}
	}
	else
		return (1);
	return (0);
}

int	handle_1_philo(t_phil	*philo)
{
	take_left_fork(philo);
	ft_usleep(get_die_time(philo->data));
	pthread_mutex_unlock(philo->left_f);
	change_state(philo, DEAD);
	return (1);
}

int	start_process(int argc, char **argv)
{
	t_data	data;

	if (init_data(&data, argc, argv) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	init_philo(&data);
	init_forks(&data);
	start_threads(&data);
	free_data(&data);
	return (0);
}

int	ft_usleep(uint64_t sleep_time)
{
	uint64_t	start;

	start = get_time();
	while ((get_time() - start) < sleep_time)
		usleep(500);
	return (0);
}

uint64_t	start_time(t_data	*data)
{
	uint64_t	time;

	pthread_mutex_lock(&data->mut_time_start);
	time = data->time_start;
	pthread_mutex_unlock(&data->mut_time_start);
	return (time);
}
