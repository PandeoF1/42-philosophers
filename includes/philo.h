/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 03:40:55 by tnard             #+#    #+#             */
/*   Updated: 2021/12/28 04:12:44 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "../ft_printf/ft_printf.h"
# include <pthread.h>

typedef struct s_philo
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				count_eat;
	int				count_eat_max;
	int				time_start;
	int				time_end;
	pthread_mutex_t	*mutex;
	pthread_t		*thread;
}	t_philo;

int		ft_check_arg(int argc, char *argv[]);
int		ft_atoi(char *str);
void	ft_init(t_philo *philo, int argc, char **argv);

#endif