/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukkyaa <rukkyaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 17:00:30 by axlamber          #+#    #+#             */
/*   Updated: 2023/01/20 00:44:18 by rukkyaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	eat(t_philo *voltaire)
{
	pthread_mutex_lock(&voltaire->data->forks[voltaire->l_fork]);
	print_msg(voltaire, "fork");
	pthread_mutex_lock(&voltaire->data->forks[voltaire->r_fork]);
	print_msg(voltaire, "fork");
	print_msg(voltaire, "eat");
	voltaire->last_eat = current_time();
	ft_usleep(voltaire->data->time_to_eat);
	pthread_mutex_unlock(&voltaire->data->forks[voltaire->l_fork]);
	pthread_mutex_unlock(&voltaire->data->forks[voltaire->r_fork]);
}

void	*routine(void *philo)
{
	t_philo	*socrate;
	
	socrate = (t_philo *)philo;
	if (!(socrate->id % 2))
		ft_usleep(socrate->data->time_to_eat / 2);
	while (!socrate->data->is_dead)
	{
		eat(socrate);
		print_msg(socrate, "sleep");
		ft_usleep(socrate->data->time_to_sleep);
		print_msg(socrate, "think");
	}
	return (NULL);
}

void	check_death(t_data *data)
{
	int	i;
	
	while (!data->is_dead)
	{
		i = -1;
		while ((unsigned int)++i < data->nb_philo)
		{
			if (current_time() - data->philos[i].last_eat >= data->time_to_die)
			{
				print_msg(&data->philos[i], "dead");
				data->is_dead = 1;
				break ;
			}
			ft_usleep(100);
		}
	}
}