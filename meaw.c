/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meaw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboonpro <pboonpro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 15:24:05 by pboonpro          #+#    #+#             */
/*   Updated: 2023/08/25 13:36:06 by pboonpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start(t_set *set)
{
	int	i;

	i = 0;
	while (i < set->log.num_phi)
	{
		set->id = i;
		set->philo[i].born = get_time();
		pthread_create(&set->philo[i].th, NULL, &routine, set);
		pthread_detach(set->philo[i].th);
		usleep(100);
		i += 2;
		if (i >= set->log.num_phi && i % 2 == 0)
			i = 1;
	}
	return (1);
}

void	free_all(t_set *set)
{
	int	i;

	i = 0;
	if (set->fork != 0)
	{
		i = set->log.num_phi;
		while (i >= 0)
			pthread_mutex_destroy(&set->fork[i--]);
		free(set->fork);
	}
	if (set->philo != NULL)
		free(set->philo);
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
	start(&set);
	stop_check(&set);
	free_all(&set);
	return (0);
}
