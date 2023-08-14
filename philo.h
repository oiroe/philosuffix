/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboonpro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 18:32:22 by pboonpro          #+#    #+#             */
/*   Updated: 2023/08/15 02:19:16 by pboonpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>

typedef struct s_log
{
	int	num_phi;
	int	time_to_eat;
	int	time_to_die;
	int	time_to_sleep;
	int	max_eat;
}	t_log;

typedef struct s_philo
{
	pthread_t	th;
	int			phi_index;
	int			last_eat;
	int			r_fork;
	int			l_fork;
	int			count_eat;
}	t_philo;

typedef struct s_set
{
	bool			death;
	t_log			log;
	t_philo			*philo;
	pthread_mutex_t	*fork;
}	t_set;

int		ft_atoi(const char *str);
long	get_time(void);

#endif
