/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 17:00:30 by axlamber          #+#    #+#             */
/*   Updated: 2023/01/18 17:17:57 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	*routine(void *philo)
{
	t_philo	*socrate;

	socrate = (t_philo *)philo;
	if (!(socrate->id % 2))
		ft_usleep(socrate->data->time_to_eat / 2);
	printf("Bonjour, je suis le philo numero %d !\n", socrate->id);
	return (NULL);
}