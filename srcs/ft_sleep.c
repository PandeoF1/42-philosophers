/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sleep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 17:16:20 by tnard             #+#    #+#             */
/*   Updated: 2021/12/29 20:45:47 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_msleep(int ms)
{
	unsigned int	x;
	unsigned int	time;

	time = get_time();
	x = time;
	while (x < time + ms)
	{	
		x = get_time();
		usleep(10);
	}
}

void	ft_sleep(t_philos *philo)
{
	pthread_mutex_lock(&philo->master->print);
	ft_printf("%u %d is sleeping\n", get_time() - philo->master->start,
		philo->id);
	pthread_mutex_unlock(&philo->master->print);
	ft_msleep(philo->master->time_to_sleep);
	philo->status = 2;
}
