/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 03:41:56 by tnard             #+#    #+#             */
/*   Updated: 2021/12/29 20:48:15 by tnard            ###   ########lyon.fr   */
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
		//ft_printf("thread - init - time : %d\n", philo.start);
		ft_create_thread(&philo);
		philo.status = 1;
		philo.start = get_time();
		while (philo.status != -1 && philo.count_eat != philo.nb_philo)
			usleep(10);
		//ft_printf("thread - end - time : %d - elapsed : %d\n", get_time(), get_time() - philo.start);
	}
	else
		ft_usage();
	return (0);
}
