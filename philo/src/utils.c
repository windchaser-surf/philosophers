/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwechsle <fwechsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:58:15 by felix             #+#    #+#             */
/*   Updated: 2024/01/29 18:59:14 by fwechsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	time_last_meal(t_thread *philo)
{
	if (ft_get_time() - philo->last_eat >= philo->time_to_die)
	{
		pthread_mutex_lock(philo->death);
		if (*philo->death_philo == 0)
			printf("%u  %d died\n", ft_get_current_time(philo), \
				philo->n_philo);
		*philo->death_philo = 1;
		pthread_mutex_unlock(philo->death);
		return (1);
	}
	return (0);
}

int	ft_print_message(t_thread *philo, char *message)
{
	pthread_mutex_lock(philo->death);
	if (*philo->death_philo == 1)
	{
		pthread_mutex_unlock(philo->death);
		return (1);
	}
	else
		printf("%u %u %s\n", ft_get_current_time(philo), philo->n_philo, \
			message);
	pthread_mutex_unlock(philo->death);
	return (0);
}

int	ft_ate_enough(t_thread *philo)
{
	if (philo->number_of_times_each_philo_must_eat == -1)
		return (0);
	else if (philo->number_of_times_each_philo_must_eat == philo->n_eaten)
		return (1);
	else
		return (0);
}

void	ft_just_sleep(unsigned int time)
{
	unsigned int	start;

	start = ft_get_time();
	while ((ft_get_time() - start) < time)
		usleep(300);
}

int	ft_sleep(unsigned int time, t_thread *philo, char *message, int flag)
{
	unsigned int	start;

	if (time_last_meal(philo) || ft_ate_enough(philo))
		return (1);
	if (ft_print_message(philo, message))
		return (1);
	if (flag == 1)
		philo->last_eat = ft_get_time();
	start = ft_get_time();
	while ((ft_get_time() - start) < time)
	{
		if (time_last_meal(philo))
			return (1);
		usleep(300);
	}
	return (0);
}
