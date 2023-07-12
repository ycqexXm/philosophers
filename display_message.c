/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_message.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yorlians <yorlians@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 01:14:36 by yorlians          #+#    #+#             */
/*   Updated: 2023/06/30 13:32:56 by yorlians         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	print an error message to the standart output and optionally print the
							program's usage.
*/
int	error_message(char *message, int print_usage)
{
	put_string(message, STDOUT_FILENO);
	put_string("\n", STDOUT_FILENO);
	if (print_usage == 1)
	{
		printf("\033[31m");
		printf("Usage: ./philo <number_of_philosophers> <time_to_die> ");
		printf("<time_to_eat> <time_to_sleep>\n");
		printf("[number_of_times_each_philosopher_must_eat]\n");
		printf("\033[0m");
	}
	return (EXIT_FAILURE);
}

/*
	check various fields in the t_table structure and call error_message
	with the appropriate error message if any of the conditions are not met.
*/
int	error_message_args(t_table *table)
{
	if (table -> philos_num < 1)
		return (error_message(PHILO_NUM, 0));
	if (table -> time_to_die <= 0)
		return (error_message(DEATH_TIME, 0));
	if (table -> time_to_eat <= 0)
		return (error_message(FOOD_TIME, 0));
	if (table -> time_to_sleep <= 0)
		return (error_message(SLEEP_TIME, 0));
	return (0);
}

/*
	printing the action performed by a philosopher along with the
		corresponding timestamp and the id of the philosopher
*/
void	print_info(t_data_philo *philo, char *action)
{
	long int	time;

	pthread_mutex_lock(philo -> write_message);
	time = get_time_now() - *philo -> start_time;
	if (time >= 0 && time <= 2147483647 && alive_check(philo))
		printf("[%d] Philo: %d %s\n", (int)time, philo -> philo_id, action);
	pthread_mutex_unlock(philo -> write_message);
}
