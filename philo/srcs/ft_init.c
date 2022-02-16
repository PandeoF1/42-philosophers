/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 04:02:22 by tnard             #+#    #+#             */
/*   Updated: 2022/02/16 14:50:57 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_init(t_philo *philo, int argc, char **argv)
{
	philo->status = 0;
	pthread_mutex_init(&philo->eat, NULL);
	philo->count_eat = 0;
	philo->nb_fork = ft_atoi(argv[1]);
	pthread_mutex_init(&philo->print, NULL);
	philo->nb_philo = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo->count_eat_max = ft_atoi(argv[5]);
	else
		philo->count_eat_max = -1;
	philo->thread = malloc(sizeof(pthread_t) * philo->nb_philo);
	if (!philo->thread)
	{
		printf("Error: malloc\n");
		exit(0);
	}
}

void	ft_config_last(t_philos **philo)
{
	t_philos	*tmp;
	int			i;

	tmp = (*philo);
	i = 0;
	while (tmp->next)
	{
		tmp = tmp->next;
		i++;
	}
	if (i != 0)
		(*philo)->fork_left = &tmp->fork_right;
	else
		(*philo)->fork_left = NULL;
}

void	ft_thread_min(t_philos *philos, int *x)
{
	if (philos->status == 0)
		ft_eat(philos, (*x)++);
	else if (philos->status == 1)
		ft_sleep(philos);
	else if (philos->status == 2)
		ft_think(philos);
	else if (philos->status == 3)
		ft_kill_me(philos);
}
