/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meaw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboonpro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 15:24:05 by pboonpro          #+#    #+#             */
/*   Updated: 2023/08/10 00:40:21 by pboonpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_h(void)
{
	printf("Error\n");
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t		i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	av_check(char **av, int ac)
{
	size_t	i;
	int		j;
	char	*temp;

	j = 1;
	while (j < ac)
	{
		temp = av[j];
		i = 0;
		while (i < ft_strlen(temp))
		{
			if (!ft_isdigit(temp[i]))
				return (0);
			i++;
		}
		j++;
	}
	return (1);
}

int	setup(char **av, t_set *set, int ac)
{
	if (!av_check(av, ac))
		return (0);
	set->death = 0;
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

	set->fork = malloc(sizeof(pthread_t) * set->log.num_phi);
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

/*void	*routine(void *set)
{
	return (NULL);
}*/

int	main(int ac, char **av)
{
	t_set	set;

	if (ac != 5 && ac != 6)
		return (error_h());
	if (!setup(av, &set, ac))
		return (error_h());
	if (!fork_init(&set))
		return (error_h());
	return (0);
}
