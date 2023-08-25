/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboonpro <pboonpro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 13:22:31 by pboonpro          #+#    #+#             */
/*   Updated: 2023/08/25 13:22:47 by pboonpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	setup(char **av, t_set *set, int ac)
{
	if (!av_check(av, ac))
		return (0);
	set->fork = 0;
	set->philo = NULL;
	set->death = 0;
	set->id = 0;
	set->log.num_phi = ft_atoi(av[1]);
	set->log.time_to_die = ft_atoi(av[2]);
	set->log.time_to_eat = ft_atoi(av[3]);
	set->log.time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		set->log.max_eat = ft_atoi(av[5]);
	else
		set->log.max_eat = -1;
	if (!check(set))
		return (0);
	return (1);
}

int	fork_init(t_set *set)
{
	int	i;

	set->fork = malloc(sizeof(pthread_mutex_t) * set->log.num_phi);
	if (!set->fork)
		return (0);
	i = 0;
	while (i < set->log.num_phi)
	{
		if (pthread_mutex_init(&set->fork[i], NULL) != 0)
		{
			while (i >= 0)
				pthread_mutex_destroy(&set->fork[i--]);
			free(set->fork);
			return (0);
		}
		i++;
	}
	return (1);
}

int	philo_init(t_set *set)
{
	int	i;

	set->philo = malloc(sizeof(t_philo) * set->log.num_phi);
	if (!set->philo)
		return (0);
	i = 0;
	while (i < set->log.num_phi)
	{
		set->philo[i].th = 0;
		set->philo[i].phi_index = i;
		set->philo[i].r_fork = (i + 1) % set->log.num_phi;
		set->philo[i].l_fork = i;
		set->philo[i].count_eat = 0;
		set->philo[i].finish = 0;
		i++;
	}
	return (1);
}
