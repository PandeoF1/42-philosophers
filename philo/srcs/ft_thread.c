/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 14:54:33 by tnard             #+#    #+#             */
/*   Updated: 2022/02/16 15:01:48 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int64_t	get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (int64_t)1000) + (tv.tv_usec / 1000));
}

void	ft_free(t_philo *philo)
{
	t_philos	*tmp;
	t_philos	*tmp1;

	tmp = philo->philos->next;
	while (tmp)
	{
		tmp1 = tmp->next;
		free(tmp);
		tmp = tmp1;
	}
	free(philo->thread);
	pthread_mutex_destroy(&philo->print);
}

void	ft_kill_me(t_philos *philo)
{
	pthread_mutex_lock(&philo->master->print);
	printf("%lld %lld died\n", get_time() - philo->master->start,
		philo->id);
	pthread_mutex_unlock(&philo->master->print);
	philo->master->status = -1;
}

void	*ft_thread(void *ph)
{
	t_philos	*philos;
	int			x;

	x = -1;
	philos = (t_philos *)ph;
	philos->time_to_die = get_time();
	while (philos->master->status != -1)
	{
		if (philos->master->status == 0)
			usleep(10);
		else if (x == -1 && philos->id % 2 == 0)
		{
			x = 0;
			ft_think(philos);
			ft_msleep(philos->master->time_to_eat - 1, philos);
		}
		else if (x == philos->master->count_eat_max)
		{
			philos->master->count_eat++;
			x += 10;
		}
		else
			ft_thread_min(philos, &x);
	}
	return (NULL);
}

void	ft_create_thread(t_philo *philo, int i)
{
	t_philos	*phi;

	phi = malloc(sizeof(t_philos));
	philo->philos = phi;
	phi->id = i;
	pthread_mutex_init(&phi->fork_right, NULL);
	phi->master = philo;
	phi->status = 2;
	if (pthread_create(&philo->thread[i - 1], NULL, ft_thread, (void *)phi))
		printf("Error: pthread_create\n");
	pthread_detach(philo->thread[i - 1]);
	while (i++ < philo->nb_philo)
	{
		phi->next = malloc(sizeof(t_philos));
		phi->next->id = i;
		phi->next->status = 2;
		pthread_mutex_init(&phi->next->fork_right, NULL);
		phi->next->fork_left = &phi->fork_right;
		phi->next->master = philo;
		phi = phi->next;
		if (pthread_create(&philo->thread[i - 1], NULL, ft_thread, (void *)phi))
			printf("Error: pthread_create\n");
		pthread_detach(philo->thread[i - 1]);
	}
}
