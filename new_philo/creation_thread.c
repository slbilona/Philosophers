/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creation_thread.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 12:32:25 by ilona             #+#    #+#             */
/*   Updated: 2023/07/06 18:54:13 by ilona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Crée la liste chainée et les threads
int	ft_creation_table(t_struct *ma_structure)
{
	t_philosophe	*actuel;
	t_philosophe	*temp;
	int				i;

	i = 0;
	ma_structure->philosophe = NULL;
	while (i < ma_structure->info.nb_de_philos)
	{
		actuel = ft_lstadd_back(&ma_structure->philosophe, ft_lstnew(i));
		if (!actuel)
			return (1);
		if (i != 0)
			actuel->fourchette_g = &temp->fourchette_d;
		temp = actuel;
		i++;
	}
	if (i >= 1)
		ma_structure->philosophe->fourchette_g = &actuel->fourchette_d;
	ft_lancement_thread(ma_structure);
	ft_vide_liste(ma_structure);
	printf("parfait\n");
	return (0);
}

//	Lance chaque threads 
int	ft_lancement_thread(t_struct *ma_structure)
{
	t_philosophe	*actuel;

	actuel = ma_structure->philosophe;
	ma_structure->actuel = NULL;
	while (actuel)
	{
		//printf("ft_lancement_thread\n");
		if(ma_structure->actuel == NULL)
		{
			//printf("actuel->i : %d\n", actuel->i);
			ma_structure->actuel = actuel;
			if (pthread_create(&actuel->philo, NULL, ft_philo, ma_structure))
			{
				printf("la création du thread numero %d a echouée\n", actuel->i);
				return (1);
			}
			actuel = actuel->next;
		}
	}
	return (ft_join(ma_structure));
}

// Utilise la fontion pthread_join sur tous les threads
int	ft_join(t_struct *ma_structure)
{
	t_philosophe	*actuel;

	actuel = ma_structure->philosophe;
	while (actuel)
	{
		if (pthread_join(actuel->philo, NULL))
		{
			printf("le join numero %d a echoue\n", actuel->i);
			return (1);
		}
		actuel = actuel->next;
	}
	return (0);
}
