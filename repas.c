/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repas.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilselbon <ilselbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 12:36:59 by ilona             #+#    #+#             */
/*   Updated: 2023/07/23 00:26:53 by ilselbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Fonction principale de chaque thread
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
			if (ft_print(tab, "is thinking"/*		🤔"*/, 0))
				return (NULL);
			tab->sdk = 3;
		}
	}
	return (NULL);
}

// Compte le nombre de repas qu'a pris le philosophe
void	ft_compte_repas(t_philosophe *actuel)
{
	if (actuel->info->notepme != -1)
	{
		pthread_mutex_lock(&actuel->mutex);
		actuel->nb_de_repas++;
		if (actuel->nb_de_repas == actuel->info->notepme)
			actuel->i_ate = 1;
		pthread_mutex_unlock(&actuel->mutex);
	}
}

// Les philosophes prennent leur fourchettes et mangent
int	ft_eat(t_philosophe *actuel)
{
	if (actuel->i % 2 == 0)
	{
		if (ft_gauchers(actuel))
			return (1);
	}
	else
		if (ft_droitiers(actuel))
			return (1);
	if (ft_print(actuel, "is eating"/*		🍝"*/, 1))
	{
		pthread_mutex_unlock(actuel->fourchette_g);
		pthread_mutex_unlock(&actuel->fourchette_d);
		return (1);
	}
	ft_usleep(actuel->info->tte, actuel);
	ft_compte_repas(actuel);
	ft_lache_fourchette(actuel);
	return (0);
}

// Libère les fouchettes
void	ft_lache_fourchette(t_philosophe *actuel)
{
	pthread_mutex_unlock(actuel->fourchette_g);
	pthread_mutex_unlock(&actuel->fourchette_d);
	actuel->sdk = 2;
}
