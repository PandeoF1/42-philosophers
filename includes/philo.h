/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 03:40:55 by tnard             #+#    #+#             */
/*   Updated: 2021/12/31 15:34:38 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "../ft_printf/ft_printf.h"
# include <pthread.h>
# include <stdint.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_philos
{
	int64_t				id;
	int64_t				status;
	int64_t				time_to_die;
	struct s_philo		*master;
	struct s_philos		*next;
	struct s_philos		*prev;
}	t_philos;

typedef struct s_philo
{
	int64_t				status;
	pthread_mutex_t		print;
	int64_t				nb_fork;
	int64_t				nb_philo;
	int64_t				time_to_die;
	int64_t				time_to_eat;
	int64_t				time_to_sleep;
	int64_t				count_eat_max;
	int64_t				count_eat;
	int64_t				start;
	struct s_philos		*philos;
	pthread_t			*thread;
}	t_philo;

int				ft_check_arg(int argc, char *argv[]);
int				ft_atoi(char *str);
void			ft_init(t_philo *philo, int argc, char **argv);
void			ft_create_thread(t_philo *philo);
void			ft_eat(t_philos *philo, unsigned int a);
void			ft_sleep(t_philos *philo);
void			ft_think(t_philos *philo);
int64_t			get_time(void);
void			ft_msleep(int ms, t_philos *philos);
int				ft_death(t_philo *philo);
void			ft_free(t_philo *philo);

#endif