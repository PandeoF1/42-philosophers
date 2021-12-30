/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 17:01:27 by tnard             #+#    #+#             */
/*   Updated: 2021/12/29 23:35:04 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_eat(t_philos *philo, unsigned int a)
{
	while (philo->master->nb_fork < 2)
		usleep(10);
	philo->master->nb_fork -= 2;
	a = get_time();
	pthread_mutex_lock(&philo->master->print);
	ft_printf("%u %d has taken a fork\n", get_time() - philo->master->start,
		philo->id);
	ft_printf("%u %d has taken a fork\n", get_time() - philo->master->start,
		philo->id);
	ft_printf("%u %d is eating\n", get_time() - philo->master->start,
		philo->id);
	pthread_mutex_unlock(&philo->master->print);
	ft_msleep(philo->master->time_to_eat);
	philo->time_to_die = get_time();
	philo->master->nb_fork += 2;
	philo->status = 1;
	philo->time_to_die = get_time() + (get_time() - a);
}
