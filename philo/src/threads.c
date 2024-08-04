/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwechsle <fwechsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:29:32 by fwechsle          #+#    #+#             */
/*   Updated: 2024/01/29 16:00:56 by fwechsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_create_threads(t_data *rules)
{
	unsigned int	i;

	i = 0;
	while (i < rules->n_of_philo)
	{
		rules->philo[i].n_philo = i + 1;
		if (pthread_create(rules->philo_th + i, NULL, &ft_routine, \
			(void *)&rules->philo[i]))
		{
			pthread_mutex_lock(&rules->death);
			rules->death_code = 1;
			pthread_mutex_unlock(&rules->death);
			return (err_msg("Thread create failed"), 1);
		}
		rules->success_th_creation++;
		i++;
	}
	return (0);
}

int	ft_thread_join(t_data *rules)
{
	int	i;

	i = 0;
	while (i < rules->success_th_creation)
	{
		if (pthread_join(rules->philo_th[i], NULL) != 0)
			return (err_msg("Thread join failed"), 1);
		i++;
	}
	return (0);
}

int	ft_init_threads(t_data *rules)
{
	int	exit_code;

	exit_code = 0;
	if (ft_create_mutex(rules))
		return (1);
	exit_code = ft_create_threads(rules);
	if (exit_code == 0)
		exit_code = ft_thread_join(rules);
	else
		ft_thread_join(rules);
	if (ft_destroy_mutex(rules))
		return (1);
	return (exit_code);
}
