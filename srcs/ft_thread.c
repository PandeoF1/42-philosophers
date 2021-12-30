/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 14:54:33 by tnard             #+#    #+#             */
/*   Updated: 2021/12/30 02:27:19 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
	ft_printf("%u %d died\n", get_time() - philo->master->start,
		philo->id);
	pthread_mutex_unlock(&philo->master->print);
	philo->master->status = -1;
}

void	*ft_thread(void *ph)
{
	t_philos	*philos;
	int			x;

	x = 0;
	philos = (t_philos *)ph;
	while (philos->master->status != -1)
	{
		if (philos->master->status == 0)
			usleep(10);
		else if (x == philos->master->count_eat_max)
		{
			philos->master->count_eat++;
			x += 10;
		}
		else if (philos->status == 0)
			ft_eat(philos, x++);
		else if (philos->status == 1)
			ft_sleep(philos);
		else if (philos->status == 2)
			ft_think(philos);
		else if (philos->status == 3)
			ft_kill_me(philos);
	}
	return (NULL);
}

void	ft_create_thread(t_philo *philo)
{
	t_philos	*philos;
	int			i;

	philos = malloc(sizeof(t_philos));
	i = 1;
	philo->philos = philos;
	philos->id = i;
	philos->time_to_die = get_time();
	philos->master = philo;
	if (pthread_create(&philo->thread[i], NULL, ft_thread, (void *)philos))
		ft_printf("Error: pthread_create\n");
	pthread_detach(philo->thread[i]);
	while (i++ < philo->nb_philo)
	{
		philos->next = malloc(sizeof(t_philos));
		philos->next->id = i;
		philos->next->time_to_die = get_time();
		philos->next->master = philo;
		philos = philos->next;
		if (pthread_create(&philo->thread[i], NULL, ft_thread, (void *)philos))
			ft_printf("Error: pthread_create\n");
		pthread_detach(philo->thread[i]);
	}	
}
