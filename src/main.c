/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-ppe <joao-ppe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:34:50 by joao-ppe          #+#    #+#             */
/*   Updated: 2024/01/03 12:04:03 by joao-ppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int ac, char **av)
{
	t_data	*data;

	if ((ac != 5 && ac != 6) || check_input(av))
	{
		printf("Error: Invalid arguments.\n");
		return (1);
	}
	data = init_data(ac, av);
	if (!data)
	{
		free_data(data);
		free(data);
		return (1);
	}
	reunion(data);
	free_data(data);
	printf("the end.\n");
	//write(1, "\n", 1);
	return (0);
}
