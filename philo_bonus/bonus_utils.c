/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acetin <acetin@student.42kocaeli.com.tr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:14:52 by acetin            #+#    #+#             */
/*   Updated: 2022/06/27 15:14:55 by acetin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_isdigit(char **arg)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (arg[i][j])
	{
		j = 0;
		while (arg[i][j])
		{
			if (arg[i][j] < '0' || arg[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	sem_create(t_common *common)
{
	common->semaphore.fork_name = "/fork_for_philo";
	common->semaphore.print_name = "/print_for_philo";
	sem_unlink(common->semaphore.fork_name);
	sem_unlink(common->semaphore.print_name);
	common->semaphore.forks = sem_open(common->semaphore.fork_name,
			O_CREAT, S_IRUSR | S_IWUSR, common->number_of_philosophers);
	common->semaphore.print = sem_open(common->semaphore.print_name,
			O_CREAT, S_IRUSR | S_IWUSR, 1);
	if (common->semaphore.forks == SEM_FAILED
		|| common->semaphore.print == SEM_FAILED)
	{
		printf("semphore fail\n");
		exit(EXIT_FAILURE);
	}
}

void	*kill_process(void *philo)
{
	int			i;
	int			ret;
	t_common	*common;

	common = (t_common *)philo;
	i = 0;
	ret = 0;
	waitpid(-1, &ret, 0);
	if (ret != 0)
	{
		sem_close(common->semaphore.forks);
		sem_close(common->semaphore.print);
		sem_unlink(common->semaphore.fork_name);
		sem_unlink(common->semaphore.print_name);
		while (i < common->number_of_philosophers)
		{
			kill(common->philosophers[i].pid, SIGKILL);
			i++;
		}
	}
	return (NULL);
}
