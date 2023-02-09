/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:28:54 by axlamber          #+#    #+#             */
/*   Updated: 2023/02/09 14:23:54 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	get_info(t_data *data)
{
	printf("Nb philo : %d\n", data->nb_philo);
	printf("Time to die : %d\n", data->time_to_die);
	printf("Time to eat : %d\n", data->time_to_eat);
	printf("Time to sleep : %d\n", data->time_to_sleep);
	printf("Nb meal : %d\n", data->nb_of_meal);
}

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
	int	i;

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
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->nb_philo);
	if (!data->forks)
		return (true);
	i = -1;
	while ((unsigned int)++i < data->nb_philo)
		pthread_mutex_init(&data->forks[i], NULL);
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->death, NULL);
	pthread_mutex_init(&data->meal, NULL);
	return (false);
}

/*
** Function to init the philosophers
**
** @param data: data structure to init
**
** @return: true if the arguments are valid, false otherwise
*/
bool	init_philos(t_data *data)
{
	int	i;

	data->philos = (t_philo *)malloc(data->nb_philo * sizeof(t_philo));
	if (!data->philos)
		return (true);
	i = -1;
	while ((unsigned int)++i < data->nb_philo)
		data->philos[i].total_meal = 0;
	i = -1;
	while ((unsigned int)++i < data->nb_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].last_eat = current_time();
		data->philos[i].data = data;
		data->philos[i].l_fork = i;
		if ((unsigned int)i == data->nb_philo - 1)
			data->philos[i].r_fork = 0;
		else
			data->philos[i].r_fork = i + 1;
		if (pthread_create(&data->philos[i].thread, NULL, \
			&routine, &(data->philos[i])))
			return (true);
	}
	check_death(data);
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
	if (init_philos(data))
	{
		free(data->philos);
		return (true);
	}
	return (false);
}
