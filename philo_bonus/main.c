/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukkyaa <rukkyaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 16:50:44 by axlamber          #+#    #+#             */
/*   Updated: 2023/02/14 15:48:28 by rukkyaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	free_all(t_data *data)
{
	free(data->philos);
	sem_close(data->forks);
	sem_close(data->print);
	sem_close(data->meal);
	sem_close(data->death);
	sem_close(data->check);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		pids[2000];
	int		i;
	int		status;

	if (parsing(argc, argv, &data))
		return (EXIT_FAILURE);
	i = -1;
	while (++i < data.nb_philo)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			routine_philo(&data.philos[i]);
			return (0);
		}
	}
	i = -1;
	while (++i < data.nb_philo)
		waitpid(-1, &status, 0);
	free_all(&data);
	return (EXIT_SUCCESS);
}
