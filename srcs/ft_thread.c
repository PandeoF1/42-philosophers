/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 14:54:33 by tnard             #+#    #+#             */
/*   Updated: 2021/12/29 20:59:52 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*ft_thread(void *ph)
{
	t_philos	*philos;
	int			x;

	x = 0;
	philos = (t_philos *)ph;
	while (philos->master->status != -1)
	{
		philos->time_to_die = get_time();
		if (philos->master->status == 0)
			usleep(10);
		if (x == philos->master->count_eat_max)
		{
			philos->master->count_eat++;
			x += 10;
		}
		else if (philos->status == 0)
		{
			ft_eat(philos);
			x++;
		}
		else if (philos->status == 1)
			ft_sleep(philos);
		else if (philos->status == 2)
			ft_think(philos);
		else if (philos->status == 3)
		{
			pthread_mutex_lock(&philos->master->print);
			ft_printf("%u %d died\n", get_time() - philos->master->start,
				philos->id);
			pthread_mutex_unlock(&philos->master->print);
			philos->master->status = -1;
			break ;
		}
	}
}

void	ft_create_thread(t_philo *philo)
{
	t_philos	*philos;
	t_philos	*tmp;
	int			i;

	i = 1;
	philos = malloc(sizeof(t_philos));
	philo->philos = philos;
	philos->id = i;
	philos->master = philo;
	if (pthread_create(&philo->thread[i], NULL, ft_thread, (void *)philos))
		ft_printf("Error: pthread_create\n");
	pthread_detach(philo->thread[i]);
	while (i++ < philo->nb_philo)
	{
		philos->next = malloc(sizeof(t_philos));
		philos->next->id = i;
		philos->next->master = philo;
		philos = philos->next;
		if (pthread_create(&philo->thread[i], NULL, ft_thread, (void *)philos))
			ft_printf("Error: pthread_create\n");
		pthread_detach(philo->thread[i]);
	}	
}
