/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meaw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboonpro <pboonpro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 15:24:05 by pboonpro          #+#    #+#             */
/*   Updated: 2023/08/18 17:47:58 by pboonpro         ###   ########.fr       */
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

int	setup(char **av, t_set *set, int ac)
{
	if (!av_check(av, ac))
		return (0);
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
		set->philo[i].last_eat = 0;
		set->philo[i].r_fork = (i + 1) % set->log.num_phi;
		set->philo[i].l_fork = i;
		set->philo[i].count_eat = 0;
		set->philo[i].finish = 0;
		i++;
	}
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
		if (set->philo[i].count_eat != set->log.max_eat \
				&& set->log.max_eat != -1 && !set->philo[i].finish)
		{
			philo_full++;
			set->philo[i].finish = 1;
		}
		if (now(set->philo[i].last_eat) > set->log.time_to_die)
		{
			set->death = 1;
			printf("YOU DIE\n");
			return ;
		}
		usleep(100);
		i++;
		i = i % set->log.num_phi;
	}
}

void	eating(t_set *set, int i)
{
	if (set->death || pthread_mutex_lock(&set->fork[set->philo[i].l_fork]))
		return ;
	if (set->death || pthread_mutex_lock(&set->fork[set->philo[i].r_fork]))
		return ;
	printf("%ld %d has taken a fork\n", now(set->start), i);
	printf("%ld %d is eating\n", now(set->start), i);
}

void	unlock(t_set *set, int i)
{
	if (set->death || pthread_mutex_unlock(&set->fork[set->philo[i].l_fork]))
		return ;
	if (set->death || pthread_mutex_unlock(&set->fork[set->philo[i].r_fork]))
		return ;
}

void	*routine(void *se)
{
	t_set	*set;
	int		i;

	set = (t_set *)se;
	i = set->id;
	set->philo[i].last_eat = set->start;
	while (!set->death && (set->philo[i].count_eat < set->log.max_eat \
			|| set->log.max_eat == -1))
	{
		eating(set, i);
		set->philo[i].last_eat = get_time();
		time_pass(set->log.time_to_eat, set);
		if (set->death)
			return (NULL);
		unlock(set, i);
		set->philo[i].count_eat++;
		if (set->philo[i].count_eat == set->log.max_eat)
			return (NULL);
		printf("%ld %d is sleeping\n", now(set->start), i);
		time_pass(set->log.time_to_sleep, set);
		if (set->death)
			return (NULL);
		printf("%ld %d is thinking\n", now(set->start), i);
	}
	return (NULL);
}

int	start(t_set *set)
{
	int	i;

	i = 0;
	while (i < set->log.num_phi)
	{
		set->id = i;
		set->start = get_time();
		pthread_create(&set->philo[i].th, NULL, &routine, set);
		pthread_detach(set->philo[i].th);
		usleep(100);
		i += 2;
		if (i >= set->log.num_phi && i % 2 == 0)
			i = 1;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_set	set;

	if (ac != 5 && ac != 6)
		return (error_h());
	if (!setup(av, &set, ac))
		return (error_h());
	if (!fork_init(&set))
		return (error_h());
	if (!philo_init(&set))
		return (error_h());
	//printf("%d\n", set.philo[1].l_fork);
	//printf("%d\n", set.philo[1].r_fork);
	start(&set);
	stop_check(&set);
	return (0);
}
