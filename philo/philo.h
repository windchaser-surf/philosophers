/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwechsle <fwechsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:50:30 by felix             #+#    #+#             */
/*   Updated: 2024/01/29 18:17:38 by fwechsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# define MAX_UI 4294967295

typedef struct s_thread
{
	unsigned int	n_philo;
	unsigned int	n_of_philo;
	int				n_eaten;
	unsigned int	last_eat;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	timestamp;
	int				number_of_times_each_philo_must_eat;
	int				*death_philo;
	pthread_mutex_t	*death;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
}	t_thread;

typedef struct s_data
{
	unsigned int	n_of_philo;
	unsigned int	start_time;
	int				death_code;
	int				success_th_creation;
	pthread_mutex_t	death;
	int				mutex_init_death;
	pthread_mutex_t	*forks;
	int				mutex_init_forks;
	pthread_t		*philo_th;
	t_thread		*philo;
}				t_data;

//init.c
int				check_init_input(int argc, char **argv, t_data *rules);
char			*ft_skip_spaces(char *number);
int				value_is_negativ(char *number);
void			init_philos(t_thread *philo, char **argv, int argc, \
				t_data *rules);
int				init_data(t_data *rules, int argc, char **argv);

//init_utils.c
void			init_philo_while(t_data *rules, int argc, char **argv);

//logic.c
void			*ft_routine(void *data);
int				ft_eat_odd(t_thread *philo);
int				ft_eat_even(t_thread *philo);
void			fork_unlock(pthread_mutex_t *first, pthread_mutex_t *second, \
				pthread_mutex_t *death);

//main.c
void			err_msg(char *str);
void			free_all(t_data *rules);

//mutex.c
int				ft_create_mutex(t_data *rules);
void			err_destroy_mutex(t_data *rules);
int				ft_destroy_mutex(t_data *rules);

//utils.c
int				ft_sleep(unsigned int time, t_thread *philo, char *message, \
				int flag);
int				ft_print_message(t_thread *philo, char *message);
int				time_last_meal(t_thread *philo);
int				ft_ate_enough(t_thread *philo);
void			ft_just_sleep(unsigned int time);

//utils_2.c
unsigned int	ft_get_time(void);
unsigned int	ft_get_current_time(t_thread *philo);
size_t			ft_strlen(const char *s);
void			ft_putstr_fd(char *s, int fd);
long long		ft_atoi(const char *str);

//threads.c
int				ft_init_threads(t_data *rules);

#endif