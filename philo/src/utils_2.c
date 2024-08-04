/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwechsle <fwechsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 12:52:33 by fwechsle          #+#    #+#             */
/*   Updated: 2024/01/29 18:17:20 by fwechsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

unsigned int	ft_get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (err_msg("Error with getting time of the day"), 1);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

unsigned int	ft_get_current_time(t_thread *philo)
{
	unsigned int	current_time;

	current_time = ft_get_time() - philo->timestamp;
	return (current_time);
}

size_t	ft_strlen(const char *s)
{
	size_t		length;

	length = 0;
	while (*s != '\0')
	{
		s++;
		length++;
	}
	return (length);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s == 0)
		return ;
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
}

long long	ft_atoi(const char *str)
{
	int			i;
	long long	result;
	long long	pre;

	pre = 1;
	i = 0;
	result = 0;
	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			pre *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * pre);
}
