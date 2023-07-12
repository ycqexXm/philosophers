/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yorlians <yorlians@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 10:21:10 by yorlians          #+#    #+#             */
/*   Updated: 2023/06/30 13:27:14 by yorlians         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	check if all philosophers have reached the maximum number of meals. If so,
	print a message indicating that all meals have been completed and set
	the stop flag of each philosopher to 1, indicating that they should stop.
*/
int	meal_control(t_table *table, t_data_philo *philo)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&table -> main_lock);
	if (table -> already_ate_max == table -> philos_num)
	{
		printf("%s\n", FINISH_MEAL);
		while (++i < table -> philos_num)
			philo[i].stop = 1;
		pthread_mutex_unlock(&table -> main_lock);
		return (-1);
	}
	pthread_mutex_unlock(&table -> main_lock);
	return (0);
}

/*
	monitor the state of the philosophers and take appropriate actions.
	iterate over the philosophers and check if any philosopher has
	exceeded the time to die. If so, print a death message and stop.
	After checking the time to die, call meal_control to check if all
						meals have been completed
*/
void	control(t_table *table, t_data_philo *philo)
{
	int				i;

	i = -1;
	while (++i < table -> philos_num)
	{
		pthread_mutex_lock(&table -> priv_lock[i]);
		if (get_time_now() - philo[i].last_meal_time >= table -> time_to_die)
		{
			pthread_mutex_unlock(&table -> priv_lock[i]);
			pthread_mutex_lock(&table -> main_lock);
			printf("[%d] Philo: %d %s\n", \
				(int)(get_time_now() - table -> start_time), i + 1, DIE);
			i = -1;
			while (++i < table -> philos_num)
				philo[i].stop = 1;
			pthread_mutex_unlock(&table -> main_lock);
			return ;
		}
		pthread_mutex_unlock(&table -> priv_lock[i]);
		if (meal_control(table, philo) == -1)
			return ;
		if (i + 1 == table -> philos_num)
			i = -1;
	}
}
