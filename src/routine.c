/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-ppe <joao-ppe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:20:16 by joao-ppe          #+#    #+#             */
/*   Updated: 2024/01/10 23:15:59 by joao-ppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	reunion(t_data *data)
{
	int	i;

	i = -1;
	data->start_time = get_time();
	pthread_mutex_lock(&data->lock);
	while (++i < data->philo_num)
	{
		if (pthread_create(&data->table[i], NULL, &routine, &data->philos[i]))
			return ;
	}
	pthread_mutex_unlock(&data->lock);
	if (pthread_create(&data->monitor[0], NULL, &monitoring, data))
		return ;
	i = -1;
	if (pthread_join(data->monitor[0], NULL))
		return ;
	while (++i < data->philo_num)
	{
		if (pthread_join(data->table[i], NULL))
			return ;
	}
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
		if (routine_finished(philo->data))
			break ;
	}
	return (NULL);
}

void	*monitoring(void *struc)
{
	int		i;
	t_data	*data;

	data = (t_data *)struc;
	i = 0;
	pthread_mutex_lock(&data->lock);
	pthread_mutex_unlock(&data->lock);
	while (1)
	{
		pthread_mutex_lock(&data->philos[i].lock);
		if (data->philos[i].status == DEAD)
		{
			pthread_mutex_lock(&data->lock);
			data->finished = true;
			pthread_mutex_unlock(&data->lock);
			pthread_mutex_unlock(&data->philos[i].lock);
			logs(&data->philos[i], DEAD);
			break ;
		}
		pthread_mutex_unlock(&data->philos[i].lock);
		i++;
		if (i == (data->philo_num))
			i = 0;
	}
	return (NULL);
}
