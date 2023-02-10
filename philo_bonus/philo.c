/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:04:21 by axlamber          #+#    #+#             */
/*   Updated: 2023/02/10 14:28:50 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	take_fork(t_philo *aristote, bool flag)
{
	if (flag)
	{
		sem_wait(aristote->data->forks);
		print_msg(aristote, "fork");
		sem_wait(aristote->data->forks);
		print_msg(aristote, "fork");
	}
	if (!flag)
	{
		sem_post(aristote->data->forks);
		sem_post(aristote->data->forks);
	}
}

void	eat(t_philo *platon)
{
	take_fork(platon, true);
	print_msg(platon, "eat");
	sem_wait(platon->data->death);
	platon->last_eat = current_time();
	platon->total_meal++;
	sem_post(platon->data->death);
	ft_usleep(platon->data->time_to_eat);
	take_fork(platon, false);
}

void	routine_philo(t_philo *notch)
{
	print_msg(notch, "eat");
	print_msg(notch, "sleep");
	print_msg(notch, "think");
	if (!(notch->id % 2))
		ft_usleep(notch->data->time_to_eat / 2);
	while (1)
	{
		eat(notch);
		if (notch->total_meal == notch->data->nb_of_meal)
			break ;
		print_msg(notch, "sleep");
		ft_usleep(notch->data->time_to_sleep);
		print_msg(notch, "think");
	}
	sem_close(notch->data->forks);
	sem_close(notch->data->print);
	sem_close(notch->data->death);
	free(notch->data->philos);
}
