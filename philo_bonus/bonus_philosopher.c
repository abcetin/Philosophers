/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_philosopher.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acetin <acetin@student.42kocaeli.com.tr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:14:40 by acetin            #+#    #+#             */
/*   Updated: 2022/06/27 15:14:41 by acetin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	life_cycle(t_philosophers *philosopher)
{
	pthread_create(&philosopher->die, NULL, &dead, philosopher);
	while (1)
	{
		if (philosopher->common->must_eat
			&& philosopher->eat_count == philosopher->common->must_eat)
			break ;
		if (philosopher->id % 2)
			sleep_philo(2);
		eat(philosopher);
		sleeping(philosopher);
	}
	exit(1);
}

void	philosophers_process(t_common common)
{
	int	i;

	i = 0;
	common.set_time.start = get_current_time(0);
	while (i < common.number_of_philosophers)
	{
		common.philosophers[i].pid = fork();
		common.philosophers[i].common = &common;
		if (common.philosophers[i].pid < 0)
		{
			kill_process(&common);
			printf("Process Error\n");
			exit(EXIT_FAILURE);
		}
		else if (common.philosophers[i].pid == 0)
			life_cycle(&common.philosophers[i]);
		i++;
	}
	pthread_create(&common.kill, NULL, &kill_process, &common);
	pthread_join(common.kill, NULL);
}

static void	assigning_arguments(t_common *common)
{
	int	i;

	i = 0;
	sem_create(common);
	common->philosophers = (t_philosophers *)malloc(sizeof(t_philosophers)
			* common->number_of_philosophers);
	if (!common->philosophers)
	{
		printf("Memory Allocation\n");
		exit(EXIT_FAILURE);
	}
	while (i < common->number_of_philosophers)
	{
		common->philosophers[i].id = i + 1;
		common->philosophers[i].eat_count = 0;
		common->philosophers[i].last_eat = get_current_time(0);
		common->philosophers[i].common = common;
		i++;
	}
}

int	main(int ac, char **av)
{
	t_common	common;
	int			i;

	i = 0;
	if (ac != 5 && ac != 6)
	{
		printf("5 or 6 arguments are needed\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		if (!check_arg(&common, av) || !ft_isdigit(av))
		{
			printf("enter a number greater than zero\n");
			exit(EXIT_FAILURE);
		}
		assigning_arguments(&common);
		philosophers_process(common);
	}
}
