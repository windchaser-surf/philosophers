/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwechsle <fwechsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 12:20:34 by fwechsle          #+#    #+#             */
/*   Updated: 2024/01/26 13:01:23 by fwechsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_create_mutex(t_data *rules)
{
	unsigned int	i;

	i = 0;
	if (pthread_mutex_init(&rules->death, NULL) != 0)
		return (err_destroy_mutex(rules), 1);
	rules->mutex_init_death = 1;
	while (i < rules->n_of_philo)
	{
		if (pthread_mutex_init(&rules->forks[i], NULL) != 0)
			return (err_destroy_mutex(rules), 1);
		rules->philo[i].l_fork = &rules->forks[i];
		if (i == 0 && rules->n_of_philo > 1)
			rules->philo[i].r_fork = &rules->forks[rules->n_of_philo - 1];
		else if (rules->n_of_philo == 1)
			rules->philo[i].r_fork = NULL;
		else
			rules->philo[i].r_fork = &rules->forks[i - 1];
		rules->philo[i].death = &rules->death;
		rules->mutex_init_forks++;
		i++;
	}
	return (0);
}

void	err_destroy_mutex(t_data *rules)
{
	int	i;

	i = 0;
	if (rules->mutex_init_death != 0)
		pthread_mutex_destroy(&rules->death);
	while (i < rules->mutex_init_death)
	{
		pthread_mutex_destroy(&rules->forks[i]);
		i++;
	}
	err_msg("Mutex init failed");
}

int	ft_destroy_mutex(t_data *rules)
{
	unsigned int	i;

	i = 0;
	while (i < rules->n_of_philo)
	{
		if (pthread_mutex_destroy(&rules->forks[i]) != 0)
			return (err_msg("Mutex destroy"), 1);
		i++;
	}
	return (0);
}
