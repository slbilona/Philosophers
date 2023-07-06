/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repas.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 12:36:59 by ilona             #+#    #+#             */
/*   Updated: 2023/07/06 18:58:51 by ilona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//
void	*ft_philo(void *ma_structure)
{
	t_struct		*m_s;
	t_philosophe	*actuel;

	m_s = ma_structure;
	actuel = m_s->actuel;
	m_s->actuel = NULL;
	//printf("thread numero %d s'est lancé\n", actuel->i);
	while (ft_verif_philos(m_s))
	{
		actuel->time_of_death = ft_time(m_s) + m_s->info.ttd;
		if (actuel->sdk == 3 && ft_verif_philos(m_s))
		{
			if (ft_eat(m_s, actuel))
				return (NULL);
		}
		if (actuel->sdk == 2 && ft_verif_philos(m_s))
			ft_sleep(m_s, actuel);
		if (actuel->sdk == 1 && ft_verif_philos(m_s))
		{
			if(ft_think(m_s, actuel))
				return (NULL);
		}
	}
	//printf("fin d'execution thread numero %d\n", actuel->i);
	return (NULL);
}

// Les philosophes prennent leur fourchettes et mangent
int	ft_eat(t_struct *m_s, t_philosophe *actuel)
{
	unsigned long	time;
	if (actuel->i % 2 == 0)
		ft_gauchers(m_s, actuel);
	else
		ft_droitiers(m_s, actuel);
	if(actuel->time_of_death < ft_time(m_s))
		return (ft_mort(m_s, actuel), 1);
	time = ft_time(m_s);
	printf("%ld %d is eating\n", time, actuel->i);
	actuel->time_of_death = ft_time(m_s) + m_s->info.ttd;
	ft_usleep(m_s->info.tte);
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
int	ft_gauchers(t_struct *m_s, t_philosophe *actuel)
{
	unsigned long	time;
	pthread_mutex_lock(actuel->fourchette_g);
	if(actuel->time_of_death < ft_time(m_s) || !ft_verif_philos(m_s))
		return (ft_mort(m_s, actuel), 1);
	time = ft_time(m_s);
	printf("%ld %d has taken a fork\n", time, actuel->i);
	pthread_mutex_lock(&actuel->fourchette_d);
	if(actuel->time_of_death < ft_time(m_s) || !ft_verif_philos(m_s))
		return (ft_mort(m_s, actuel), 1);
	time = ft_time(m_s);
	printf("%ld %d has taken a fork\n", time, actuel->i);
	return (0);
}

// Le philosophe commence en prenant sa fourchette droite
int	ft_droitiers(t_struct *m_s, t_philosophe *actuel)
{
	unsigned long	time;
	
	pthread_mutex_lock(&actuel->fourchette_d);
	if(actuel->time_of_death < ft_time(m_s) || !ft_verif_philos(m_s))
		return (ft_mort(m_s, actuel), 1);
	time = ft_time(m_s);
	printf("%ld %d has taken a fork\n", time, actuel->i);
	pthread_mutex_lock(actuel->fourchette_g);
	if(actuel->time_of_death < ft_time(m_s) || !ft_verif_philos(m_s))
		return (ft_mort(m_s, actuel), 1);
	time = ft_time(m_s);
	printf("%ld %d has taken a fork\n", time, actuel->i);
	return (0);
}
