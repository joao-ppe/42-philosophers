/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-ppe <joao-ppe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:40:19 by joao-ppe          #+#    #+#             */
/*   Updated: 2024/01/12 17:02:13 by joao-ppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	init_philos(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_num)
	{
		data->philos[i].data = data;
		data->philos[i].id = i;
		data->philos[i].meal_count = 0;
		data->philos[i].status = -1;
		data->philos[i].full = false;
		data->philos[i].time_to_die = 0;
		data->philos[i].finished = false;
		pthread_mutex_init(&data->philos[i].lock, NULL);
	}
}

static t_data	*init_threads(t_data *data)
{
	int	i;

	i = -1;
	data->table = malloc(sizeof(pthread_t) * data->philo_num);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_num);
	data->monitor = malloc(sizeof(pthread_t) * 1);
	if (!data->table || !data->forks || !data->monitor)
		return (NULL);
	pthread_mutex_init(&data->lock, NULL);
	pthread_mutex_init(&data->log, NULL);
	while (++i < data->philo_num)
		pthread_mutex_init(&data->forks[i], NULL);
	return (data);
}

static void	set_forks(t_data *data, int i)
{
	while (++i < data->philo_num - 1)
	{
		if (i % 2)
		{
			data->philos[i].fork[LEFT] = &data->forks[i - 1];
			data->philos[i].fork[RIGHT] = &data->forks[i];
		}
		else
		{
			data->philos[i].fork[LEFT] = &data->forks[i];
			data->philos[i].fork[RIGHT] = &data->forks[i + 1];
		}
	}
	if (i % 2)
	{
		data->philos[i].fork[LEFT] = &data->forks[i - 1];
		data->philos[i].fork[RIGHT] = &data->forks[i];
	}
	else
	{
		data->philos[i].fork[LEFT] = &data->forks[i];
		data->philos[i].fork[RIGHT] = &data->forks[0];
	}
}

t_data	*init_data(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	data->philo_num = ft_atol(av[1]);
	data->death_time = (u_int64_t) ft_atol(av[2]);
	data->eat_time = (u_int64_t) ft_atol(av[3]);
	data->sleep_time = (u_int64_t) ft_atol(av[4]);
	data->finished = false;
	data->philos_full = 0;
	if (ac == 6)
		data->meals = ft_atol(av[5]);
	else
		data->meals = -1;
	data->start_time = 0;
	data->philos = malloc(sizeof(t_philo) * data->philo_num);
	if (!data->philos)
		return (NULL);
	init_threads(data);
	init_philos(data);
	set_forks(data, -1);
	return (data);
}
