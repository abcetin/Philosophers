/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acetin <acetin@student.42kocaeli.com.tr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:15:07 by acetin            #+#    #+#             */
/*   Updated: 2022/06/27 15:15:08 by acetin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_philosophers	t_philosophers;

typedef struct s_time
{
	long long	start;
	long long	time_to_die;
	long long	time_to_eat;
	long long	time_to_sleep;
}	t_time;

typedef struct s_semaphore
{
	sem_t	*forks;
	sem_t	*print;
	char	*fork_name;
	char	*print_name;
}	t_semaphore;

typedef struct s_common
{
	t_time			set_time;
	t_philosophers	*philosophers;
	pthread_t		kill;
	pthread_t		all_eat;
	t_semaphore		semaphore;
	int				i;
	int				must_eat;
	int				number_of_philosophers;
}	t_common;

typedef struct s_philosophers
{
	int			id;
	int			pid;
	pthread_t	die;
	long long	last_eat;
	int			eat_count;
	t_common	*common;
}	t_philosophers;

//-------utils------------//
int			ft_atoi(const char *str);
int			check_arg(t_common *common, char **arg);
int			ft_isdigit(char **arg);
//-------sleep------------//
void		sleep_philo(long long time);
long long	get_current_time(long long time);
//-------life-cycle------------//
void		eat(t_philosophers *philosopher);
void		*dead(void *philo);
void		sleeping(t_philosophers *philosopher);
//-------utils------------//
void		ft_print(char *mes, t_philosophers *philosopher);
void		sem_create(t_common *common);
void		*kill_process(void *phil);
void		all_eat(t_common common);
#endif
