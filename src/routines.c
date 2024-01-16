/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-ppe <joao-ppe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:20:16 by joao-ppe          #+#    #+#             */
/*   Updated: 2024/01/15 17:00:33 by joao-ppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Example 	Expected Result
./philo 4 500 200 1.2 	Invalid argument.
./philo 4 0 200 200 	Invalid argument.
./philo 4 -500 200 200 	Invalid argument.
./philo 4 214748364732 200 200 	Invalid argument.
./philo 1 200 200 200 	Philosopher 1 takes a fork and dies after 200 ms.
./philo 4 500 200 2147483647 	A philosopher dies after 500 ms
./philo 4 200 210 200 	A philosopher dies, it should display the death before 210 ms.
./philo 4 310 200 200 	A philosopher dies.
./philo 5 800 200 200 7 	The program stops when each philosopher has eaten 7 times.
./philo 5 800 200 200 	No philosopher dies.
./philo 4 2147483647 200 200 	No philosopher dies.
./philo 5 800 200 150 	No philosopher dies.
./philo 3 610 200 80 	No philosopher dies.
./philo 2 800 200 200 	No philosopher dies.
./philo 4 410 200 200 	No philosopher dies. */
#include "../include/philo.h"

/* static void	print_meals(t_data *data)
{
	int	i = -1;
	while (++i < data->philo_num)
		printf("============= Philo %d meals: %d =============\n", data->philos[i].id, data->philos[i].meal_count);
	return ;
} */

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
	if ((philo->id % 2) || philo->id == 0)
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
		if (check_philo_status(&data->philos[i]))
		{
			pthread_mutex_unlock(&data->philos[i].lock);
			break ;
		}
		pthread_mutex_unlock(&data->philos[i].lock);
		i++;
		if (i == (data->philo_num))
			i = 0;
	}
	//print_meals(data);
	return (NULL);
}
