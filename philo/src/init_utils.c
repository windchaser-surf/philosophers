/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwechsle <fwechsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 16:03:21 by fwechsle          #+#    #+#             */
/*   Updated: 2024/01/29 16:08:26 by fwechsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	init_philo_while(t_data *rules, int argc, char **argv)
{
	unsigned int	i;

	i = 0;
	while (i < rules->n_of_philo)
	{
		rules->philo[i].timestamp = rules->start_time;
		rules->philo[i].death_philo = &rules->death_code;
		init_philos(&rules->philo[i], argv, argc, rules);
		i++;
	}
}
