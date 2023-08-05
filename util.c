/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboonpro <pboonpro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 18:56:38 by pboonpro          #+#    #+#             */
/*   Updated: 2023/08/04 18:57:19 by pboonpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	checkmaxmin(int sum, int count, int sign)
{
	if (count > 19)
	{
		if (sign == -1)
			return (0);
		else
			return (-1);
	}
	return (sum * sign);
}

int	ft_atoi(const char *str)
{
	unsigned long	sum;
	int				sign;
	int				i;
	int				count;
	int				result;

	sum = 0;
	sign = 1;
	i = 0;
	count = 0;
	while (str[i] && (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		sum = (sum * 10) + str[i] - '0';
		i++;
		count++;
	}
	result = checkmaxmin(sum, count, sign);
	return (result);
}
