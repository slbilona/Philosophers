/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 12:34:56 by ilona             #+#    #+#             */
/*   Updated: 2023/07/16 19:22:12 by ilona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Transforme une string en int
int	ft_atoi(const char *nptr)
{
	int	result;
	int	i;
	int	sign;

	sign = 1;
	i = 0;
	result = 0;
	while ((9 <= nptr[i] && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + nptr[i] - 48;
		i++;
	}
	return (result * sign);
}

// Donne le temps en millisecondes depuis le lancement du programme
long int	ft_time(t_philosophe *philo)
{
	struct timeval	rn;
	long int		diff_ms;

	gettimeofday(&rn, NULL);
	diff_ms = (rn.tv_sec - philo->info->debut.tv_sec) * 1000;
	diff_ms += (rn.tv_usec - philo->info->debut.tv_usec) / 1000;
	return (diff_ms);
}

long int	ft_time_diff_ms(struct timeval debut, struct timeval actuel)
{
	long int	diff_ms;

	diff_ms = (actuel.tv_sec - debut.tv_sec) * 1000;
	diff_ms += (actuel.tv_usec - debut.tv_usec) / 1000;
	return (diff_ms);
}

// Fonction usleep recréée en millisecondes
void	ft_usleep(int tmp, t_philosophe *philo)
{
	struct timeval	debut;
	struct timeval	actuel;

	gettimeofday(&debut, NULL);
	gettimeofday(&actuel, NULL);
	while (tmp > ft_time_diff_ms(debut, actuel) && ft_verif_philos(philo))
	{
		usleep(500);
		gettimeofday(&actuel, NULL);
	}
}

// Print en utilisant des mutex
int	ft_print(t_philosophe *actuel, char *str, int eat_or_not)
{
	pthread_mutex_lock(&actuel->info->m_printf);
	if (!ft_verif_philos(actuel))
	{
		pthread_mutex_unlock(&actuel->info->m_printf);
		return (1);
	}
	if (eat_or_not == 1)
	{
		pthread_mutex_lock(&actuel->m_tod);
		actuel->time_of_death = ft_time(actuel) + actuel->info->ttd;
		pthread_mutex_unlock(&actuel->m_tod);
	}
	printf(" %ld	%d	%s\n", labs(ft_time(actuel)), actuel->i, str);
	pthread_mutex_unlock(&actuel->info->m_printf);
	return (0);
}
