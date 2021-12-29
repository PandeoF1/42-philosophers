/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 17:01:27 by tnard             #+#    #+#             */
/*   Updated: 2021/12/29 20:53:34 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_eat(t_philos *philo)
{
	unsigned int	x;
	unsigned int	time;

	time = get_time();
	x = time;
	while (philo->master->nb_fork < 2 && x <= philo->master->time_to_die + time)
	{
		usleep(10);
		x = get_time();
	}
	if (x >= philo->master->time_to_die + time)
		return ((void)(philo->status = 3));
	philo->master->nb_fork -= 2;
	pthread_mutex_lock(&philo->master->print);
	ft_printf("%u %d has taken a fork\n", get_time() - philo->master->start,
		philo->id);
	ft_printf("%u %d has taken a fork\n", get_time() - philo->master->start,
		philo->id);
	ft_printf("%u %d is eating\n", get_time() - philo->master->start,
		philo->id);
	pthread_mutex_unlock(&philo->master->print);
	ft_msleep(philo->master->time_to_eat);
	philo->master->nb_fork += 2;
	philo->status = 1;
}
