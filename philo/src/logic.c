/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwechsle <fwechsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 12:17:15 by fwechsle          #+#    #+#             */
/*   Updated: 2024/01/29 18:58:49 by fwechsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*ft_routine(void *data)
{
	t_thread	*philo;

	philo = (t_thread *)data;
	if (philo->n_philo % 2 == 0)
		usleep(500);
	while (1)
	{
		if (philo->n_philo % 2 == 0)
		{
			if (ft_eat_even(philo))
				return (NULL);
		}
		else
		{
			if (ft_eat_odd(philo))
				return (NULL);
		}
		if (ft_sleep(philo->time_to_sleep, philo, "is sleeping", 0))
			return (NULL);
		if (ft_sleep(0, philo, "is thinking", 0))
			return (NULL);
		usleep(500);
	}
	return (NULL);
}

int	ft_eat_odd(t_thread *philo)
{
	if (philo->n_of_philo == 1)
	{
		ft_just_sleep(philo->time_to_die);
		ft_print_message(philo, "died");
		return (1);
	}
	pthread_mutex_lock(philo->r_fork);
	if (ft_sleep(0, philo, "has taken a fork", 0))
		return (fork_unlock(philo->r_fork, NULL, NULL), 1);
	pthread_mutex_lock(philo->l_fork);
	if (ft_sleep(0, philo, "has taken a fork", 0))
		return (fork_unlock(philo->r_fork, philo->l_fork, NULL), 1);
	pthread_mutex_lock(philo->death);
	if (*philo->death_philo == 1)
		return (fork_unlock(philo->r_fork, philo->l_fork, philo->death), 1);
	pthread_mutex_unlock(philo->death);
	if (ft_sleep(philo->time_to_eat, philo, "is eating", 1))
		return (fork_unlock(philo->r_fork, philo->l_fork, NULL), 1);
	philo->n_eaten++;
	fork_unlock(philo->l_fork, philo->r_fork, NULL);
	return (0);
}

int	ft_eat_even(t_thread *philo)
{
	pthread_mutex_lock(philo->l_fork);
	if (ft_sleep(0, philo, "has taken a fork", 0))
		return (fork_unlock(philo->l_fork, NULL, NULL), 1);
	pthread_mutex_lock(philo->r_fork);
	if (ft_sleep(0, philo, "has taken a fork", 0))
		return (fork_unlock(philo->r_fork, philo->l_fork, NULL), 1);
	pthread_mutex_lock(philo->death);
	if (*philo->death_philo == 1)
		return (fork_unlock(philo->l_fork, philo->r_fork, philo->death), 1);
	pthread_mutex_unlock(philo->death);
	if (ft_sleep(philo->time_to_eat, philo, "is eating", 1))
		return (fork_unlock(philo->l_fork, philo->r_fork, NULL), 1);
	philo->n_eaten++;
	fork_unlock(philo->r_fork, philo->l_fork, NULL);
	return (0);
}

void	fork_unlock(pthread_mutex_t *first, pthread_mutex_t *second, \
		pthread_mutex_t *death)
{
	if (first != NULL)
		pthread_mutex_unlock(first);
	if (second != NULL)
		pthread_mutex_unlock(second);
	if (death != NULL)
		pthread_mutex_unlock(death);
}
