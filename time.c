/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yorlians <yorlians@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 04:11:12 by yorlians          #+#    #+#             */
/*   Updated: 2023/06/30 13:48:33 by yorlians         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	retrieve the current time in milliseconds
*/
long int	get_time_now(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

/*
	pause the execution for a specified duration in milliseconds
*/
void	new_sleep(int mil_sec)
{
	long int	start_time;

	start_time = get_time_now();
	while ((get_time_now() - start_time) < mil_sec)
		usleep(100);
}

/*
	responsible for waiting for all the threads in the table to
					complete their execution
*/
int	wait_threads(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table -> philos_num)
		pthread_join(table -> threads[i], NULL);
	return (1);
}
