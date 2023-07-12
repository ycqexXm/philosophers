/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yorlians <yorlians@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 04:35:21 by yorlians          #+#    #+#             */
/*   Updated: 2023/06/30 15:21:06 by yorlians         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	initialize all the necessary components for the dining philosophers
	problem simulation. allocate memory for the philos array and threads
		array based on the number of philosophers in the table
*/
int	init_all(t_table *table)
{
	table -> philos = malloc(sizeof(t_data_philo) * table -> philos_num);
	if (!table -> philos)
		return (free_all(table), -1);
	table -> threads = malloc(sizeof(pthread_t) * table -> philos_num);
	if (!table -> threads)
		return (free_all(table), -1);
	if (init_mutex(table) == -1)
		return (-1);
	table -> already_ate_max = 0;
	init_philo(table, table -> philos);
	init_threads(table);
	return (0);
}

/*
	initialize each philosopher in the philos array. set the philosopher
	ID, start time, left and right forks (if applicable), the number of times
	to eat, last meal time, stop flag, and various timing parameters. also
	set the pointers to shared resources such as the already_ate_max counter,
			main lock, private lock, and write message mutex.
*/
void	init_philo(t_table *table, t_data_philo *philo)
{
	int	i;

	i = -1;
	while (++i < table -> philos_num)
	{
		philo[i].philo_id = i + 1;
		philo[i].start_time = &table -> start_time;
		philo[i].left_fork = &table -> forks[i];
		if (table -> philos_num > 1)
			philo[i].right_fork = &table -> forks[(i + 1)
				% table -> philos_num];
		else
			philo[i].right_fork = NULL;
		philo[i].ate_x_times = 0;
		philo[i].eat_x_times = table -> eat_x_times;
		philo[i].last_meal_time = get_time_now();
		philo[i].stop = 0;
		philo[i].time_to_die = table->time_to_die;
		philo[i].time_to_eat = table -> time_to_eat;
		philo[i].time_to_sleep = table -> time_to_sleep;
		philo[i].already_ate_max = &table -> already_ate_max;
		philo[i].main_lock = &table -> main_lock;
		philo[i].priv_lock = &table -> priv_lock[i];
		philo[i].write_message = &table -> write_message;
	}
}

/*
	initialize the mutexes for forks, private locks, and other
	shared resources. allocate memory for the forks array and
	priv_lock array based on the number of philosophers in the table.
	then iterate over each philosopher and initialize the
		corresponding mutexes using pthread_mutex_init.
*/
int	init_mutex(t_table *table)
{
	int		i;

	i = -1;
	table -> forks = malloc(table -> philos_num * sizeof(pthread_mutex_t));
	if (!table -> forks)
		return (free_all(table), -1);
	table -> priv_lock = malloc(table -> philos_num * sizeof(pthread_mutex_t));
	if (!table -> priv_lock)
		return (free_all(table), -1);
	while (++i < table -> philos_num)
	{
		pthread_mutex_init(&table -> forks[i], NULL);
		pthread_mutex_init(&table -> priv_lock[i], NULL);
	}
	pthread_mutex_init(&table -> main_lock, NULL);
	pthread_mutex_init(&table -> write_message, NULL);
	return (0);
}

/*
	create threads for each philosopher and start their execution.
	set the start time of the simulation and then create a thread for
	each philosopher using pthread_create, passing the address of the
	philo_routine function and the corresponding philos array element
							as arguments.
*/
int	init_threads(t_table *table)
{
	int	i;

	i = -1;
	table -> start_time = get_time_now();
	while (++i < table -> philos_num)
		pthread_create(&table -> threads[i], NULL,
			&philo_routine, &table -> philos[i]);
	return (1);
}
