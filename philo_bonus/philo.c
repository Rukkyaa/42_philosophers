/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukkyaa <rukkyaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:04:21 by axlamber          #+#    #+#             */
/*   Updated: 2023/02/14 15:47:11 by rukkyaa          ###   ########.fr       */
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
	sem_wait(platon->data->meal);
	platon->last_eat = current_time();
	platon->total_meal++;
	sem_post(platon->data->meal);
	ft_usleep(platon->data->time_to_eat, platon->data);
	take_fork(platon, false);
}

void	*death_check(void *philo)
{
	t_philo	*platon;

	platon = (t_philo *)philo;
	sem_wait(platon->data->death);
	sem_wait(platon->data->check);
	platon->data->is_dead = true;
	sem_post(platon->data->check);
	sem_post(platon->data->death);
	return (NULL);
}

void	*meal_check(void *philo)
{
	t_philo	*socrate;

	socrate = (t_philo *)philo;
	while (1)
	{
		if (is_dead(socrate->data))
			break ;
		sem_wait(socrate->data->meal);
		if (current_time() - socrate->last_eat >= socrate->data->time_to_die)
		{
			sem_wait(socrate->data->print);
			if (!is_dead(socrate->data))
				printf("%lld %d died\n", current_time() - socrate->data->start_time, socrate->id);
			sem_post(socrate->data->death);
			sem_wait(socrate->data->check);
			socrate->data->is_dead = true;
			sem_post(socrate->data->check);
			sem_post(socrate->data->meal);
			usleep(10000);
			sem_post(socrate->data->print);
			break ;
		}
		if (socrate->total_meal >= socrate->data->nb_of_meal && socrate->data->nb_of_meal != -1)
		{
			sem_post(socrate->data->meal);
			sem_post(socrate->data->death);
			break ;
		}
		sem_post(socrate->data->meal);
		usleep(1000);
	}
	return (NULL);
}

void	routine_philo(t_philo *notch)
{
	print_msg(notch, "think");
	pthread_create(&notch->meal_thread, NULL, &meal_check, notch);
	pthread_create(&notch->death_thread, NULL, &death_check, notch);
	if (!(notch->id % 2))
		ft_usleep(notch->data->time_to_eat / 2, notch->data);
	while (!is_dead(notch->data))
	{
		eat(notch);
		if (notch->total_meal == notch->data->nb_of_meal)
			break ;
		print_msg(notch, "sleep");
		ft_usleep(notch->data->time_to_sleep, notch->data);
		print_msg(notch, "think");
	}
	pthread_join(notch->death_thread, NULL);
	pthread_join(notch->meal_thread, NULL);
	sem_close(notch->data->forks);
	sem_close(notch->data->print);
	sem_close(notch->data->meal);
	sem_close(notch->data->death);
	sem_close(notch->data->check);
	free(notch->data->philos);
}
