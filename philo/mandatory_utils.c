/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandatory_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acetin <acetin@student.42kocaeli.com.tr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:13:55 by acetin            #+#    #+#             */
/*   Updated: 2022/06/27 15:13:56 by acetin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n'
		|| c == '\v' || c == '\f'
		|| c == '\r' || c == 32)
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int				i;
	unsigned long	ret;
	int				isnegative;

	i = 0;
	ret = 0;
	isnegative = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
		isnegative *= -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		ret = (ret * 10) + (str[i] - '0');
		i++;
	}
	if (ret > 2147483647 && isnegative != -1)
		return (-1);
	if (ret > 2147483648 && isnegative == -1)
		return (0);
	return (ret * isnegative);
}

int	check_arg(t_common *common, char **arg)
{
	common->number_of_philosophers = ft_atoi(arg[1]);
	common->set_time.time_to_die = ft_atoi(arg[2]);
	common->set_time.time_to_eat = ft_atoi(arg[3]);
	common->set_time.time_to_sleep = ft_atoi(arg[4]);
	if (common->number_of_philosophers <= 0)
		return (0);
	else if (common->set_time.time_to_die <= 0)
		return (0);
	else if (common->set_time.time_to_eat <= 0)
		return (0);
	else if (common->set_time.time_to_sleep <= 0)
		return (0);
	else if (arg[5] != NULL)
	{
		common->number_of_times_each_philosopher_must_eat = ft_atoi(arg[5]);
		if (common->number_of_times_each_philosopher_must_eat <= 0)
			return (0);
	}
	return (1);
}
