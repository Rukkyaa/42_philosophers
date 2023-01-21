/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:04:31 by axlamber          #+#    #+#             */
/*   Updated: 2023/01/21 15:40:39 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	free_all(t_data *data)
{
	int	i;

	i = -1;
	while ((unsigned int)++i < data->nb_philo)
	{
		pthread_join(data->philos[i].thread, NULL);
		pthread_mutex_destroy(&data->forks[i]);
	}
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->death);
	free(data->philos);
	free(data->forks);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (parsing(argc, argv, &data))
		return (EXIT_FAILURE);
	free_all(&data);
	return (EXIT_SUCCESS);
}
