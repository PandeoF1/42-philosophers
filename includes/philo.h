/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 03:40:55 by tnard             #+#    #+#             */
/*   Updated: 2021/12/30 02:06:32 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "../ft_printf/ft_printf.h"
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_philos
{
	int				id;
	int				status;
	unsigned int	time_to_die;
	struct s_philo	*master;
	struct s_philos	*next;
	struct s_philos	*prev;
}	t_philos;

typedef struct s_philo
{
	int				status;
	pthread_mutex_t	print;
	int				nb_fork;
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				count_eat_max;
	int				count_eat;
	unsigned int	start;
	struct s_philos	*philos;
	pthread_t		*thread;
}	t_philo;

int				ft_check_arg(int argc, char *argv[]);
int				ft_atoi(char *str);
void			ft_init(t_philo *philo, int argc, char **argv);
void			ft_create_thread(t_philo *philo);
void			ft_eat(t_philos *philo, unsigned int a);
void			ft_sleep(t_philos *philo);
void			ft_think(t_philos *philo);
unsigned int	get_time(void);
void			ft_msleep(int ms);
int				ft_death(t_philo *philo);
void			ft_free(t_philo *philo);

#endif