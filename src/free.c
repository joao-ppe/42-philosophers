/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-ppe <joao-ppe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:20:18 by joao-ppe          #+#    #+#             */
/*   Updated: 2024/01/12 17:02:34 by joao-ppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	free_data(t_data *data)
{
	int	i;

	if (!data)
		return ;
	i = -1;
	while (++i < data->philo_num)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos->lock);
	}
	pthread_mutex_destroy(&data->lock);
	pthread_mutex_destroy(&data->log);
	if (data->monitor)
		free(data->monitor);
	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
	if (data->table)
		free(data->table);
	if (data)
		free(data);
}
