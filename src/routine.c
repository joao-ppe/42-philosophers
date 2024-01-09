/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-ppe <joao-ppe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:20:16 by joao-ppe          #+#    #+#             */
/*   Updated: 2024/01/03 14:26:30 by joao-ppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	reunion(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time();
	pthread_mutex_lock(&data->lock);
	while (i < data->philo_num)
	{
		if (pthread_create(&data->table[i], NULL, &routine, &data->philos[i]))
			return ;
		i++;
	}
	pthread_mutex_unlock(&data->lock);
	if (pthread_create(&data->monitor[0], NULL, &monitoring, data))
		return ;
	pthread_join(data->monitor[0], NULL);
	return ;
}

void	*routine(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	pthread_mutex_lock(&philo->data->lock);
	pthread_mutex_unlock(&philo->data->lock);
	pthread_mutex_lock(&philo->lock);
	philo->time_to_die = philo->data->death_time + philo->data->start_time;
	pthread_mutex_unlock(&philo->lock);
	if (philo->id % 2 == 0)
		thinking(philo);
	while (1)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
		pthread_mutex_lock(&philo->data->lock);
		if (philo->data->finished == true)
		{
			pthread_mutex_lock(&philo->lock);
			philo->finished = true;
			pthread_mutex_unlock(&philo->lock);
			break ;
		}
		pthread_mutex_unlock(&philo->data->lock);

	}
	return (NULL);
}

void	*monitoring(void *struc)
{
	int		i;
	t_data	*data;

	data = (t_data *)struc;
	i = 0;
	while (1)
	{
		pthread_mutex_lock(&data->lock);
		pthread_mutex_lock(&data->philos[i].lock);
		if (data->philos[i].status == DEAD)
		{
			logs(&data->philos[i], DEAD);
			data->finished = true;
			pthread_mutex_unlock(&data->lock);
			pthread_mutex_unlock(&data->philos[i].lock);
			break ;
		}
		pthread_mutex_unlock(&data->philos[i].lock);
		pthread_mutex_unlock(&data->lock);
		i++;
		if (i == (data->philo_num))
			i = 0;
	}
	i = -1;
	while (++i < data->philo_num)
	{
		//printf("Terminou o monitor %d\n", i);
		pthread_mutex_lock(&data->philos[i].lock);
		if (data->philos[i].finished)
			pthread_join(data->table[i], NULL);	
		pthread_mutex_unlock(&data->philos[i].lock);
	}
	return (NULL);
}