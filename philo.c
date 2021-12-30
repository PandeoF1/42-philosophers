/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 03:41:56 by tnard             #+#    #+#             */
/*   Updated: 2021/12/30 05:16:41 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

long	ft_atol(char *str)
{
	long	res;
	int		sign;

	res = 0;
	sign = 1;
	while (*str && *str >= '0' && *str <= '9')
		res = res * 10 + *str++ - '0';
	return (res * sign);
}

int	ft_atoi(char *str)
{
	int	i;
	int	nb;
	int	neg;

	i = 0;
	nb = 0;
	neg = 1;
	if (str[i] == '-')
	{
		i++;
		neg = -1;
	}
	while (str[i] != '\0')
	{
		nb = nb * 10 + str[i] - '0';
		i++;
	}
	return (nb * neg);
}

int	ft_check_arg(int argc, char *argv[])
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (ft_atol(argv[i] + j) > 2147483647)
				return (0);
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	ft_usage(void)
{
	write(2, "./philo [nb_philo] [time_to_die]", 33);
	write(2, " [time_to_eat] [time_to_sleep]", 31);
	write(2, " [max eat(optional)]\n", 22);
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
	{
		ft_usage();
		return (-1);
	}
	return (0);
}
