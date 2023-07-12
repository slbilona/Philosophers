/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 12:34:56 by ilona             #+#    #+#             */
/*   Updated: 2023/07/12 13:08:12 by ilona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//transforme une string en int
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

// Donne le temps en micro-seconde depuis le lancement du programme
long int	ft_time(t_philosophe *philo)
{
	struct timeval	rn;

	gettimeofday(&rn, NULL);
	return ((rn.tv_usec - philo->info->debut.tv_usec) / 1000);
}

long int	ft_time2(struct timeval debut)
{
	struct timeval	rn;

	gettimeofday(&rn, NULL);
	return ((rn.tv_usec - debut.tv_usec) / 1000);
}

void	ft_usleep(int tmp, t_philosophe *philo)
{
	long			debut;
	long			actuel;
	struct timeval	deb;

	gettimeofday(&deb, NULL);
	debut = ft_time2(deb);
	actuel = debut;
	while (tmp >= (actuel - debut) && ft_verif_philos(philo))
		actuel = ft_time2(deb);
}

void	ft_destroy(t_struct *m_s)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&m_s->info.m_printf);
	pthread_mutex_destroy(&m_s->info.mutex_mort);
	if (m_s->tab)
	{
		while (i < m_s->info.nb_de_philos)
		{
			pthread_mutex_destroy(&m_s->tab[i].fourchette_d);
			pthread_mutex_destroy(&m_s->tab[i].mutex);
			i++;
		}
		free(m_s->tab);
	}
}

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
		pthread_mutex_lock(&actuel->mutex);
		actuel->time_of_death = ft_time(actuel) + actuel->info->ttd;
		pthread_mutex_unlock(&actuel->mutex);
	}
	printf("%ld %d %s\n", ft_time(actuel), actuel->i, str);
	pthread_mutex_unlock(&actuel->info->m_printf);
	return (0);
}
