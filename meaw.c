/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meaw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboonpro <pboonpro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 15:24:05 by pboonpro          #+#    #+#             */
/*   Updated: 2023/08/05 18:35:36 by pboonpro         ###   ########.fr       */
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

void	*routine(void *set)
{
	return (NULL);
}

int	main(int ac, char **av)
{
	t_set	set;

	if (ac != 5 && ac != 6)
		return (error_h());
	if (!setup(av, &set, ac))
		return (error_h());
	//if (!setup)
	return (0);
}
