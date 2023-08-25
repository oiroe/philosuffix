/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboonpro <pboonpro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 13:20:37 by pboonpro          #+#    #+#             */
/*   Updated: 2023/08/25 13:20:56 by pboonpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_set *set, int i)
{
	printf("%ld %d is thinking\n", now(set->philo[i].born), i + 1);
	if (set->death || pthread_mutex_lock(&set->fork[set->philo[i].l_fork]))
		return ;
	printf("%ld %d has taken a fork\n", now(set->philo[i].born), i + 1);
	if (set->death || pthread_mutex_lock(&set->fork[set->philo[i].r_fork]))
		return ;
	printf("%ld %d has taken a fork\n", now(set->philo[i].born), i + 1);
	printf("%ld %d is eating\n", now(set->philo[i].born), i + 1);
}

void	unlock(t_set *set, int i)
{
	if (set->death || pthread_mutex_unlock(&set->fork[set->philo[i].l_fork]))
		return ;
	if (set->death || pthread_mutex_unlock(&set->fork[set->philo[i].r_fork]))
		return ;
}

void	*routine(void *old)
{
	t_set	*set;
	int		i;

	set = (t_set *)old;
	i = set->id;
	set->philo[i].last_eat = set->philo[i].born;
	while (!set->death && (set->philo[i].count_eat < set->log.max_eat \
			|| set->log.max_eat == -1))
	{
		eating(set, i);
		set->philo[i].last_eat = get_time();
		if (time_pass(set->log.time_to_eat, set))
			return (NULL);
		unlock(set, i);
		set->philo[i].count_eat++;
		if (set->philo[i].count_eat == set->log.max_eat)
			return (NULL);
		printf("%ld %d is sleeping\n", now(set->philo[i].born), i + 1);
		if (time_pass(set->log.time_to_sleep, set))
			return (NULL);
	}
	return (NULL);
}
