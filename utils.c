/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 22:42:28 by rmitache          #+#    #+#             */
/*   Updated: 2023/10/28 03:19:21 by rmitache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign *= -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - '0';
		str++;
	}
	return (result * sign);
}

void	free_data(t_data *data)
{
	int		i;
	int		nb_phil;

	i = -1;
	nb_phil = get_nb_phil(data);
	while (++i < nb_phil)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].mut_last_eat_time);
		pthread_mutex_destroy(&data->philos[i].mut_nbr_of_meals);
		pthread_mutex_destroy(&data->philos[i].mut_state);
	}
	pthread_mutex_destroy(&data->mut_nbr_philos);
	pthread_mutex_destroy(&data->mut_str);
	pthread_mutex_destroy(&data->mut_time_start);
	pthread_mutex_destroy(&data->mut_time_eat);
	pthread_mutex_destroy(&data->mut_time_die);
	pthread_mutex_destroy(&data->mut_time_sleep);
	pthread_mutex_destroy(&data->mut_loop);
	free(data->philo_thread);
	free(data->philos);
	free(data->forks);
}

int	iter(t_data	*data)
{
	bool	keep_iter;

	pthread_mutex_lock(&data->mut_loop);
	keep_iter = data->keep_loop;
	pthread_mutex_unlock(&data->mut_loop);
	return (keep_iter);
}

void	write_message(t_data	*data, int id, char	*str)
{
	uint64_t	time;

	time = get_time() - start_time(data);
	pthread_mutex_lock(&data->mut_str);
	if (iter(data))
		printf("%llu %d %s\n", time, id, str);
	pthread_mutex_unlock(&data->mut_str);
}

void	print_instructions(void)
{
	printf(RED "Bruh... Incorrect Arguments!\n\n" RESET);
	printf("Please run like the following:\n");
	printf(GREEN "./philo 5 800 200 200" LIGHT_BLUE" 3\n" RESET);
	printf("\nRequirements:\n");
	printf(YELLOW "Number of Philos:" RESET " 1 - 200\n" RESET);
	printf(YELLOW "Time to die:" RESET " " ">= 60\n" RESET);
	printf(YELLOW "Time to eat:" RESET " " ">= 60\n" RESET);
	printf(YELLOW "Time to sleep:" RESET " >= 60\n" RESET);
	printf(LIGHT_BLUE "(Optional) " YELLOW "Number of times a Philo ");
	printf("should eat:" RESET " >= 1\n" RESET);
}
