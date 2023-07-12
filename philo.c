/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yorlians <yorlians@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 19:53:04 by yorlians          #+#    #+#             */
/*   Updated: 2023/06/30 13:40:55 by yorlians         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	allocate memory for the table structure. parse and validate the command
	line arguments. initialize all the necessary components for the simulation.
	start the simulation. Once the simulation is complete, wait for threads to
		finish execution. destroy all mutexes. free all allocated memory
*/
int	main(int argc, char **argv)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (set_check_args(table, argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_all(table) == -1)
		return (EXIT_FAILURE);
	control(table, table -> philos);
	wait_threads(table);
	destroy(table);
	free_all(table);
}
