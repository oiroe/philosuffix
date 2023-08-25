/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboonpro <pboonpro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 13:24:27 by pboonpro          #+#    #+#             */
/*   Updated: 2023/08/25 16:07:54 by pboonpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	av_check(char **av, int ac)
{
	size_t	i;
	int		j;

	j = 1;
	while (j < ac)
	{
		i = 0;
		while (av[j][i])
		{
			if (!ft_isdigit(av[j][i]))
				return (0);
			i++;
		}
		if (ft_atoi(av[j]) == 0)
			return (0);
		j++;
	}
	return (1);
}

int	check(t_set *set)
{
	if (set->log.num_phi > 200 || set->log.num_phi <= 0)
		return (0);
	if (set->log.time_to_die <= 0)
		return (0);
	if (set->log.time_to_eat <= 0)
		return (0);
	if (set->log.time_to_sleep <= 0)
		return (0);
	if (set->log.time_to_eat == 0)
		return (0);
	return (1);
}

void	stop_check(t_set *set)
{
	int	i;
	int	philo_full;

	i = 0;
	philo_full = 0;
	while (!set->death && philo_full != set->log.num_phi)
	{
		if (set->philo[i].count_eat == set->log.max_eat \
				&& set->log.max_eat != -1 && !set->philo[i].finish)
		{
			philo_full++;
			set->philo[i].finish = 1;
		}
		if (now(set->philo[i].last_eat) > set->log.time_to_die)
		{
			set->death = 1;
			printf("%ld %d died\n", now(set->philo[i].born), i + 1);
			return ;
		}
		usleep(10);
		i++;
		i = i % set->log.num_phi;
	}
}
