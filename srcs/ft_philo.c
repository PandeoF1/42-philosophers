/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 17:01:27 by tnard             #+#    #+#             */
/*   Updated: 2021/12/30 05:22:56 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_msleep(int ms)
{
	int64_t	x;
	int64_t	time;

	time = get_time();
	x = time;
	while (x < time + ms)
	{	
		x = get_time();
		usleep(10);
	}
}

int	ft_death(t_philo *philo)
{
	t_philos	*tmp;
	int64_t		time;

	tmp = philo->philos;
	while (tmp)
	{
		time = get_time();
		if (tmp->time_to_die + (int64_t)philo->time_to_die < time)
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

void	ft_think(t_philos *philo)
{
	pthread_mutex_lock(&philo->master->print);
	ft_printf("%u %d is thinking\n", get_time() - philo->master->start,
		philo->id);
	pthread_mutex_unlock(&philo->master->print);
	philo->status = 0;
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
