/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 03:41:56 by tnard             #+#    #+#             */
/*   Updated: 2021/12/30 02:09:39 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	ft_usage(void)
{
	ft_printf("./philo [nb_philo] [time_to_die]");
	ft_printf(" [time_to_eat] [time_to_sleep]");
	ft_printf(" [number_of_times_each_philosopher_must_eat (optional)]\n");
}

int	main(int argc, char *argv[])
{
	t_philo		philo;

	if ((argc == 6 || argc == 5) && ft_check_arg(argc, argv))
	{
		ft_init(&philo, argc, argv);
		ft_create_thread(&philo);
		philo.start = get_time();
		philo.status = 1;
		while (ft_death(&philo) && philo.status != -1
			&& philo.count_eat != philo.nb_philo)
			usleep(10);
		usleep(100);
		ft_free(&philo);
	}
	else
		ft_usage();
	return (0);
}