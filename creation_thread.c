/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creation_thread.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilselbon <ilselbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 12:32:25 by ilona             #+#    #+#             */
/*   Updated: 2023/07/11 05:51:09 by ilselbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_init_tab(t_struct *ma_structure)
{
	int i;

	i = 0;
	while(i < ma_structure->info.nb_de_philos)
	{
		ma_structure->tab[i].i = i + 1;
		ma_structure->tab[i].vie = 0;
		ma_structure->tab[i].sdk = 3;
		ma_structure->tab[i].nb_de_repas = 0;
		ma_structure->tab[i].fourchette_g = NULL;
		ma_structure->tab[i].philo = i;
		ma_structure->tab[i].ate = 0;
		ma_structure->tab[i].info = &ma_structure->info;
		ma_structure->tab[i].time_of_death = ma_structure->info.ttd;
		pthread_mutex_init(&ma_structure->tab->fourchette_d, NULL);
		i++;
	}
}

int	ft_creation_table(t_struct *ma_structure)
{
	int i;

	i = 0;
	ma_structure->tab = malloc(sizeof(t_philosophe) * ma_structure->info.nb_de_philos);
	if(!ma_structure->tab)
		return 1;
	ft_init_tab(ma_structure);
	i = ma_structure->info.nb_de_philos - 1;
	while(i >= 0)
	{
		if(i != 0)
			ma_structure->tab[i].fourchette_g = &ma_structure->tab[i - 1].fourchette_d;
		else
			ma_structure->tab[i].fourchette_g = &ma_structure->tab[ma_structure->info.nb_de_philos - 1].fourchette_d;
		i--;
	}
	ft_lancement_thread(ma_structure);
	//free le tableau
	printf("parfait\n");
	return (0);
}

//	Lance chaque threads 
int	ft_lancement_thread(t_struct *ma_structure)
{
	int i;

	i = 0;
	while (i < ma_structure->info.nb_de_philos)
	{
		if (pthread_create(&ma_structure->tab[i].philo, NULL, ft_philo, &ma_structure->tab[i]))
		{
			printf("la création du thread numero %d a echouée\n", ma_structure->tab[i].i);
			return (1);
		}
		i++;
	}
	check_death(ma_structure);
	return (ft_join(ma_structure));
}

// Utilise la fontion pthread_join sur tous les threads
int	ft_join(t_struct *ma_structure)
{
	int i;

	i = 0;
	while (i < ma_structure->info.nb_de_philos)
	{
		if (pthread_join(ma_structure->tab[i].philo, NULL))
		{
			printf("le join numero %d a echoue\n", ma_structure->tab[i].i);
			return (1);
		}
		i++;
	}
	return (0);
}
