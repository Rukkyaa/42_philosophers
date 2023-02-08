/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukkyaa <rukkyaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 23:25:49 by rukkyaa           #+#    #+#             */
/*   Updated: 2023/02/08 23:32:41 by rukkyaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

/*
** Function to check if the arguments are valid
**
** @param argc: number of arguments
** @param argv: arguments
** @param data: data structure to init
**
** @return: true if the arguments are valid, false otherwise
*/
bool	init_data(int argc, char **argv, t_data *data)
{
	data->is_dead = false;
	data->nb_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->start_time = current_time();
	if (argc == 6)
		data->nb_of_meal = ft_atoi(argv[5]);
	else
		data->nb_of_meal = -1;
	data->forks = sem_open("fork", O_CREAT | O_EXCL, S_IRWXU, data->nb_philo);
	data->print = sem_open("print", O_CREAT | O_EXCL, S_IRWXU, 1);
	return (false);
}

/*
** Function to init the data structure with the arguments
**
** @param argc: number of arguments
** @param argv: arguments
** @param data: data structure to init
**
** @return: true if the arguments are valid, false otherwise
*/
bool	parsing(int argc, char **argv, t_data *data)
{
	if (argc != 5 && argc != 6)
		return (true);
	if (init_data(argc, argv, data))
		return (true);
	return (false);
}
