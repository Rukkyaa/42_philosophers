/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukkyaa <rukkyaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 17:00:30 by axlamber          #+#    #+#             */
/*   Updated: 2023/01/19 10:53:16 by rukkyaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	*routine(void *philo)
{
	t_philo	*socrate;
	int		i;
	
	i = 0;
	socrate = (t_philo *)philo;
	if (!(socrate->id % 2))
		ft_usleep(socrate->data->time_to_eat / 2);
	while (!socrate->data->is_dead)
	{
		pthread_mutex_lock(&socrate->data->forks[socrate->l_fork]);
		print_msg(socrate, "fork");
		pthread_mutex_lock(&socrate->data->forks[socrate->r_fork]);
		print_msg(socrate, "fork");
		print_msg(socrate, "eat");
		ft_usleep(socrate->data->time_to_eat);
		pthread_mutex_unlock(&socrate->data->forks[socrate->l_fork]);
		pthread_mutex_unlock(&socrate->data->forks[socrate->r_fork]);
		print_msg(socrate, "sleep");
		ft_usleep(socrate->data->time_to_sleep);
		print_msg(socrate, "think");
	}
	return (NULL);
}


// 10
// 0 1
// 1 2
// 2 3
// 3 0