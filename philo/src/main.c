/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwechsle <fwechsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:51:35 by felix             #+#    #+#             */
/*   Updated: 2024/01/29 13:40:35 by fwechsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	err_msg(char *str)
{
	ft_putstr_fd(str, 2);
	write(2, "\n", 1);
}

void	free_all(t_data *rules)
{
	if (rules->forks)
		free(rules->forks);
	if (rules->philo_th)
		free(rules->philo_th);
	if (rules->philo)
		free(rules->philo);
	rules->forks = NULL;
	rules->philo_th = NULL;
	rules->philo = NULL;
}

int	main(int argc, char **argv)
{
	t_data	rules;

	rules.forks = NULL;
	rules.philo = NULL;
	rules.philo_th = NULL;
	if (check_init_input(argc, argv, &rules) != 0)
		return (free_all(&rules), 1);
	if (ft_init_threads(&rules))
		return (free_all(&rules), 1);
	free_all(&rules);
	return (0);
}
