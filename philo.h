/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboonpro <pboonpro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 18:32:22 by pboonpro          #+#    #+#             */
/*   Updated: 2023/08/25 13:26:02 by pboonpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct timeval	t_time;

typedef struct s_log
{
	int		num_phi;
	int		time_to_eat;
	int		time_to_die;
	int		time_to_sleep;
	int		max_eat;
}	t_log;

typedef struct s_philo
{
	pthread_t	th;
	int			phi_index;
	long		born;
	long		last_eat;
	int			r_fork;
	int			l_fork;
	int			count_eat;
	int			finish;
}	t_philo;

typedef struct s_set
{
	int				death;
	int				id;
	long			start;
	t_log			log;
	t_philo			*philo;
	pthread_mutex_t	*fork;
}	t_set;

int		ft_atoi(const char *str);
long	get_time(void);
int		error_h(void);
int		ft_isdigit(int c);
size_t	ft_strlen(const char *s);
long	get_time(void);
long	now(long past);
int		time_pass(long time, t_set *set);
void	free_all(t_set *set);
void	free_error(t_set *set);
void	eating(t_set *set, int i);
void	unlock(t_set *set, int i);
void	*routine(void *old);
int		setup(char **av, t_set *set, int ac);
int		fork_init(t_set *set);
int		philo_init(t_set *set);
int		av_check(char **av, int ac);
int		check(t_set *set);
void	stop_check(t_set *set);

#endif
