/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yorlians <yorlians@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 03:36:28 by yorlians          #+#    #+#             */
/*   Updated: 2023/06/30 13:47:09 by yorlians         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	represent the behavior of a philosopher thread. check if philo_id
	is even or odd. if it is they wait. This is to ensure that the philosophers
	with even IDs don't start eating simultaneously, avoiding a potential
							deadlock scenario.
*/
void	*philo_routine(void *arg)
{
	t_data_philo	*philo;

	philo = (t_data_philo *)arg;
	if (philo -> philo_id % 2 == 0)
		new_sleep(philo -> time_to_eat * 0.9);
	while (alive_check(philo))
	{
		if (meal(philo) == -1)
			return (NULL);
		if (!alive_check(philo))
			return (NULL);
		print_info(philo, SLEEP);
		new_sleep(philo -> time_to_sleep);
		print_info(philo, THINK);
	}
	return (NULL);
}

/*
	responsible for updating the meal status of the philosopher
						after each meal
*/
void	update_meal_status(t_data_philo *philo)
{
	pthread_mutex_lock(philo -> priv_lock);
	philo -> last_meal_time = get_time_now();
	pthread_mutex_unlock(philo -> priv_lock);
	if (philo -> eat_x_times != 0)
	{
		if (++philo -> ate_x_times == philo -> eat_x_times)
		{
			pthread_mutex_lock(philo -> main_lock);
			*philo -> already_ate_max += 1;
			pthread_mutex_unlock(philo -> main_lock);
		}
	}
}

/*
	ensure that philosophers take forks only when they are available,
	update their meal status, and handle cases where philosophers may
						have only one fork.
*/
int	meal(t_data_philo	*philo)
{
	if (!alive_check(philo))
		return (-1);
	pthread_mutex_lock(philo -> left_fork);
	print_info(philo, TAKE_L_FORK);
	if (!alive_check(philo))
		return (pthread_mutex_unlock(philo -> left_fork), -1);
	if (philo -> right_fork == NULL)
		return (pthread_mutex_unlock(philo -> left_fork),
			new_sleep(philo -> time_to_die * 1.1), -1);
	pthread_mutex_lock(philo -> right_fork);
	print_info(philo, TAKE_R_FORK);
	print_info(philo, EAT);
	if (!alive_check(philo))
		return (pthread_mutex_unlock(philo -> left_fork),
			pthread_mutex_unlock(philo -> right_fork), -1);
	update_meal_status(philo);
	if (!alive_check(philo))
		return (pthread_mutex_unlock(philo -> left_fork),
			pthread_mutex_unlock(philo -> right_fork), -1);
	new_sleep(philo -> time_to_eat);
	pthread_mutex_unlock(philo -> right_fork);
	pthread_mutex_unlock(philo -> left_fork);
	return (0);
}

/*
	check if the philosophers are alive
*/
int	alive_check(t_data_philo *philo)
{
	pthread_mutex_lock(philo -> main_lock);
	if (!philo -> stop)
	{
		pthread_mutex_unlock(philo -> main_lock);
		return (1);
	}
	pthread_mutex_unlock(philo -> main_lock);
	return (0);
}
