/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:04:31 by axlamber          #+#    #+#             */
/*   Updated: 2023/01/18 17:12:12 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	free_all(t_data *data)
{
	free(data->philos);
}

int main(int argc, char **argv)
{
	t_data	data;
	
	if (parsing(argc, argv, &data))
		return (EXIT_FAILURE);
	// get_info(&data);
	// printf("Timestamp : %lld\n", current_time());
	// ft_usleep(5 * 1000);
	// printf("Timestamp : %lld\n", current_time());
	free_all(&data);
	return (EXIT_SUCCESS);
}
