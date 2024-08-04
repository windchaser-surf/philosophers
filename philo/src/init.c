/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwechsle <fwechsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 14:49:11 by fwechsle          #+#    #+#             */
/*   Updated: 2024/01/29 16:08:45 by fwechsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_init_input(int argc, char **argv, t_data *rules)
{
	int	i;

	i = 1;
	if (argc < 5)
		return (err_msg("Too less arguments"), 1);
	else if (argc > 6)
		return (err_msg("Too many arguments"), 1);
	while (argv[i])
	{
		argv[i] = ft_skip_spaces(argv[i]);
		if (argv[i] == NULL)
			return (err_msg("Not a valid input (empty)"), 1);
		if (value_is_negativ(argv[i]))
			return (err_msg("Not a valid input"), 1);
		if (ft_strlen(argv[i]) > 11 || ft_atoi(argv[i]) > MAX_UI)
			return (err_msg("Not a valid input (Too big number)"), 1);
		if (ft_atoi(argv[i]) == 0)
			return (err_msg("Not a valid input (zero | not a number)"), 1);
		i++;
	}
	if (init_data(rules, argc, argv) == 1)
		return (1);
	return (0);
}

char	*ft_skip_spaces(char *number)
{
	if (!number || *number == 0)
		return (NULL);
	while (*number && (*number == ' ' || (*number >= 9 && *number <= 13)))
		number++;
	if (*number == 0)
		return (NULL);
	return (number);
}

int	value_is_negativ(char *number)
{
	if (*number == '-')
		return (1);
	if (*number == '+')
		number++;
	while (*number && (*number >= '0' && *number <= '9' ))
		number++;
	if (*number != 0)
		return (1);
	return (0);
}

void	init_philos(t_thread *philo, char **argv, int argc, t_data *rules)
{
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	philo->n_of_philo = ft_atoi(argv[1]);
	if (argc == 6)
		philo->number_of_times_each_philo_must_eat = ft_atoi(argv[5]);
	else
		philo->number_of_times_each_philo_must_eat = -1;
	(void)rules;
	philo->n_eaten = 0;
	philo->last_eat = ft_get_time();
}

int	init_data(t_data *rules, int argc, char **argv)
{
	rules->n_of_philo = ft_atoi(argv[1]);
	rules->forks = (pthread_mutex_t *)malloc(rules->n_of_philo * \
					sizeof(pthread_mutex_t));
	if (!rules->forks)
		return (err_msg("Malloc failed"), 1);
	rules->philo = (t_thread *)malloc(sizeof(t_thread) * rules->n_of_philo);
	if (!rules->philo)
		return (err_msg("Malloc failed"), 1);
	rules->philo_th = (pthread_t *)malloc (rules->n_of_philo * \
						sizeof(pthread_t));
	if (!rules->philo_th)
		return (err_msg("Malloc failed"), 1);
	rules->death_code = 0;
	rules->success_th_creation = 0;
	rules->mutex_init_death = 0;
	rules->mutex_init_forks = 0;
	rules->start_time = ft_get_time();
	init_philo_while(rules, argc, argv);
	return (0);
}
