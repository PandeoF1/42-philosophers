/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 04:02:22 by tnard             #+#    #+#             */
/*   Updated: 2021/12/29 23:55:37 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_init(t_philo *philo, int argc, char **argv)
{
	philo->status = 0;
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
		ft_printf("Error: malloc\n");
		exit(0);
	}
}
