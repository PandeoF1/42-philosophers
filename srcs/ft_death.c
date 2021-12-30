/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_death.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 21:02:53 by tnard             #+#    #+#             */
/*   Updated: 2021/12/30 02:06:38 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_death(t_philo *philo)
{
	t_philos		*tmp;
	unsigned int	time;

	tmp = philo->philos;
	while (tmp)
	{
		time = get_time();
		if (tmp->time_to_die + (unsigned int)philo->time_to_die < time)
		{
			pthread_mutex_lock(&philo->print);
			ft_printf("%u %d died\n", time - philo->start,
				tmp->id, tmp->time_to_die + philo->time_to_die, time);
			pthread_mutex_unlock(&philo->print);
			philo->status = -1;
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}
