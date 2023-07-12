/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repas.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 12:36:59 by ilona             #+#    #+#             */
/*   Updated: 2023/07/12 11:07:35 by ilona            ###   ########.fr       */
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
	if (actuel->i % 2 == 0)
	{
		if(ft_gauchers(actuel))
			return (1);
	}
	else
		if(ft_droitiers(actuel))
			return (1);
	if(ft_print(actuel, "is eating", 1))
		return (1);
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
	pthread_mutex_lock(actuel->fourchette_g);
	if (ft_print(actuel, "has taken a fork (gauche)", 0))
		return (1);
	pthread_mutex_lock(&actuel->fourchette_d);
	if (ft_print(actuel, "has taken a fork (droite)", 0))
		return (1);
	return (0);
}

// Le philosophe commence en prenant sa fourchette droite
int	ft_droitiers(t_philosophe *actuel)
{
	if(actuel->info->nb_de_philos % 2)
		ft_usleep(actuel->info->tte * 0.2, actuel);
	pthread_mutex_lock(&actuel->fourchette_d);
	if (ft_print(actuel, "has taken a fork (droite)", 0))
		return (1);
	pthread_mutex_lock(actuel->fourchette_g);
	if (ft_print(actuel, "has taken a fork (gauche)", 0))
		return (1);
	return (0);
}
