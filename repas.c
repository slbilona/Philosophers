/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repas.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilselbon <ilselbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 12:36:59 by ilona             #+#    #+#             */
/*   Updated: 2023/07/11 06:32:50 by ilselbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//
void	*ft_philo(void *philo)
{
	t_philosophe	*tab;

	tab = (t_philosophe *) philo;
	if (tab->i % 2)
		ft_usleep(tab->info->tte * 0.2, tab);
	while (ft_verif_philos(tab))
	{
		if (tab->sdk == 3 && ft_verif_philos(tab))
		{
			if (ft_eat(tab))
				return (NULL);
		}
		if (tab->sdk == 2 && ft_verif_philos(tab))
		{
			if (ft_sleep(tab))
				return (NULL);
		}
		if (tab->sdk == 1 && ft_verif_philos(tab))
		{
			if (ft_think(tab))
				return (NULL);
		}
	}
	return (NULL);
}

// Les philosophes prennent leur fourchettes et mangent
int	ft_eat(t_philosophe *actuel)
{
	unsigned long	time;

	if (actuel->i % 2 == 0)
	{
		if(ft_gauchers(actuel))
			return (1);
	}
	else
		if(ft_droitiers(actuel))
			return (1);
	pthread_mutex_lock(&actuel->info->m_printf);
	if (!ft_verif_philos(actuel))
	{
		pthread_mutex_unlock(&actuel->info->m_printf);
		return (1);
	}
	actuel->time_of_death = ft_time(actuel) + actuel->info->ttd;
	time = ft_time(actuel);
	printf("%ld %d is eating\n", time, actuel->i);
	pthread_mutex_unlock(&actuel->info->m_printf);
	ft_usleep(actuel->info->tte, actuel);
	actuel->nb_de_repas++;
	ft_lache_fourchette(actuel);
	return (0);
}

void	ft_lache_fourchette(t_philosophe *actuel)
{
	pthread_mutex_unlock(actuel->fourchette_g);
	pthread_mutex_unlock(&actuel->fourchette_d);
	actuel->sdk = 2;
}

// Le philosophe commence en prenant sa fourchette gauche
int	ft_gauchers(t_philosophe *actuel)
{
	unsigned long	time;

	pthread_mutex_lock(actuel->fourchette_g);
	pthread_mutex_lock(&actuel->info->m_printf);
	if (!ft_verif_philos(actuel))
	{
		pthread_mutex_unlock(&actuel->info->m_printf);
		return (1);
	}
	time = ft_time(actuel);
	printf("%ld %d has taken a fork (gauche)\n", time, actuel->i);
	pthread_mutex_unlock(&actuel->info->m_printf);
	pthread_mutex_lock(&actuel->fourchette_d);
	pthread_mutex_lock(&actuel->info->m_printf);
	if (!ft_verif_philos(actuel))
	{
		pthread_mutex_unlock(&actuel->info->m_printf);
		return (1);
	}
	time = ft_time(actuel);
	printf("%ld %d has taken a fork (droite)\n", time, actuel->i);
	pthread_mutex_unlock(&actuel->info->m_printf);
	return (0);
}

// Le philosophe commence en prenant sa fourchette droite
int	ft_droitiers(t_philosophe *actuel)
{
	unsigned long	time;

	if(actuel->info->nb_de_philos % 2)
		ft_usleep(actuel->info->tte * 0.2, actuel);
	pthread_mutex_lock(&actuel->fourchette_d);
	pthread_mutex_lock(&actuel->info->m_printf);
	if (!ft_verif_philos(actuel))
	{
		pthread_mutex_unlock(&actuel->info->m_printf);
		return (1);
	}
	time = ft_time(actuel);
	printf("%ld %d has taken a fork (droite)\n", time, actuel->i);
	pthread_mutex_unlock(&actuel->info->m_printf);
	pthread_mutex_lock(actuel->fourchette_g);
	pthread_mutex_lock(&actuel->info->m_printf);
	if (!ft_verif_philos(actuel))
	{
		pthread_mutex_unlock(&actuel->info->m_printf);
		return (1);
	}
	time = ft_time(actuel);
	printf("%ld %d has taken a fork (gauche)\n", time, actuel->i);
	pthread_mutex_unlock(&actuel->info->m_printf);
	return (0);
}
