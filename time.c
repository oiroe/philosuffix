/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboonpro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 01:45:37 by pboonpro          #+#    #+#             */
/*   Updated: 2023/08/15 01:45:37 by pboonpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	t_time	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

long	now(long past)
{
	long	new;
	t_time	time;

	gettimeofday(&time, NULL);
	new = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (new - past);
}

int	time_pass(long time, t_set *set)
{
	time_t	pass;

	pass = get_time();
	while (!set->death && (now(pass) < time))
		usleep(100);
	return (set->death);
}
