/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandatory_philosophers.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acetin <acetin@student.42kocaeli.com.tr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:13:36 by acetin            #+#    #+#             */
/*   Updated: 2022/06/27 15:13:41 by acetin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philosopher_life_cycle(void *philo)
{
	t_philosophers	*philosophers;

	philosophers = (t_philosophers *)philo;
	while (1)
	{
		if (philosophers->common->number_of_times_each_philosopher_must_eat > 0)
			all_eat(philosophers);
		if (philosophers->id % 2)
			sleep_philo(2);
		think(philosophers);
		take_fork(philosophers);
		eat(philosophers);
		sleeping(philosophers);
	}
	return (NULL);
}

void	create_thread(t_common *common)
{
	int			i;

	i = 0;
	pthread_mutex_init(&common->mutex, NULL);
	common->set_time.start = get_current_time(0);
	while (i < common->number_of_philosophers)
	{
		pthread_create(&common->philosophers[i].th, NULL,
			&philosopher_life_cycle, &common->philosophers[i]);
		i++;
	}
	while (--i >= 0)
		pthread_join(common->philosophers[i].th, NULL);
	pthread_mutex_destroy(&common->mutex);
}

int	creat_philosopher(t_common *common, char **arg)
{
	int	i;

	i = 0;
	if (check_arg(common, arg))
	{
		common->philosophers = (t_philosophers *)malloc(sizeof(t_philosophers)
				* common->number_of_philosophers);
		while (i < common->number_of_philosophers)
		{
			common->philosophers[i].id = i;
			common->philosophers[i].last_eat = get_current_time(0);
			common->philosophers[i].is_fork = 0;
			common->philosophers[i].state = 0;
			common->philosophers[i].eat_count = 0;
			common->philosophers[i].common = common;
			i++;
		}
		return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_common	common;

	if (ac != 5 && ac != 6)
	{
		printf("5 or 6 arguments are needed\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		if (creat_philosopher(&common, av))
			create_thread(&common);
	}
}
