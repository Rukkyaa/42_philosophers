/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 17:00:30 by axlamber          #+#    #+#             */
/*   Updated: 2023/02/15 12:51:00 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	take_fork(t_philo *boulesteix, bool flag)
{
	if (!(boulesteix->id % 2) && flag)
	{
		pthread_mutex_lock(&boulesteix->data->forks[boulesteix->l_fork]);
		print_msg(boulesteix, "fork");
		pthread_mutex_lock(&boulesteix->data->forks[boulesteix->r_fork]);
		print_msg(boulesteix, "fork");
	}
	else if (boulesteix->id % 2 && flag)
	{
		pthread_mutex_lock(&boulesteix->data->forks[boulesteix->r_fork]);
		print_msg(boulesteix, "fork");
		pthread_mutex_lock(&boulesteix->data->forks[boulesteix->l_fork]);
		print_msg(boulesteix, "fork");
	}
	if (!(boulesteix->id % 2) && !flag)
	{
		pthread_mutex_unlock(&boulesteix->data->forks[boulesteix->r_fork]);
		pthread_mutex_unlock(&boulesteix->data->forks[boulesteix->l_fork]);
	}
	else if (boulesteix->id % 2 && !flag)
	{
		pthread_mutex_unlock(&boulesteix->data->forks[boulesteix->l_fork]);
		pthread_mutex_unlock(&boulesteix->data->forks[boulesteix->r_fork]);
	}
}

void	*routine(void *philo)
{
	t_philo	*socrate;

	socrate = (t_philo *)philo;
	print_msg(socrate, "think");
	if (!(socrate->id % 2))
		ft_usleep(socrate->data->time_to_eat / 2, socrate->data);
	while (!is_dead(socrate->data) && !get_full_ate(socrate->data))
	{
		eat(socrate);
		print_msg(socrate, "sleep");
		ft_usleep(socrate->data->time_to_sleep, socrate->data);
		print_msg(socrate, "think");
		usleep(100);
	}
	return (NULL);
}

bool	is_dead(t_data *data)
{
	bool	ret;

	pthread_mutex_lock(&data->death);
	ret = data->is_dead;
	pthread_mutex_unlock(&data->death);
	return (ret);
}

long long	get_last_eat(t_philo *philo)
{
	long long	ret;

	pthread_mutex_lock(&philo->data->death);
	ret = philo->last_eat;
	pthread_mutex_unlock(&philo->data->death);
	return (ret);
}

void	check_death(t_data *data)
{
	int	i;

	while (!data->is_dead)
	{
		i = -1;
		while ((unsigned int)++i < data->nb_philo)
		{
			if (current_time() - get_last_eat(&data->philos[i])
				>= data->time_to_die)
			{
				ft_death(data, i);
				break ;
			}
			if (get_full_ate(data))
				break ;
			ft_usleep(1, data);
		}
		if (get_full_ate(data))
			break ;
	}
}
