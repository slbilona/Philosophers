/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creation_thread.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilselbon <ilselbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 22:10:30 by ilselbon          #+#    #+#             */
/*   Updated: 2023/05/04 22:28:01 by ilselbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_philo(t_philosophe *actuel)
{
	static int i;

	printf("thread philo numero %d\n", i + 1);
	if(pthread_mutex_lock(&actuel->fourchette_d) == 0)
	{
		printf("test\n");
		pthread_mutex_unlock(&actuel->fourchette_d);
	}
	return (NULL);
}

// initialise chaque maillon de la liste chainee
int	ft_initialisation(t_philosophe *actuel)
{
	if (actuel)
	{
		actuel->i = 0;
		actuel->fourchette_g = NULL;
		if(0 != pthread_mutex_init(&actuel->fourchette_d, NULL))
			return (1);
		//actuel->fourchette_d = NULL;
		actuel->nb_de_repas = 0;
		actuel->philo = 0;
		actuel->next = NULL;
	}
	return (0);
}

// initialise autant de thread qu'il y a de philosophes
int	ft_thread_philo(t_philosophe **premier)
{
	t_philosophe	*actuel;
	int				ret;
	int				i;

	i = 0;
	actuel = *premier;
	while (actuel)
	{
		ret = pthread_create(&actuel->philo, NULL, (void *)ft_philo, actuel);
		if (ret != 0)
		{
			printf("la creation du thread numero %d a echouee\n", i);
			return (1);
		}
		// ret = pthread_join(actuel->philo, NULL);
		// if (ret != 0)
		// {
		// 	printf("le join numero %d a echoue\n", i);
		// 	return (1);
		// }
		// actuel = actuel->next;
		i++;
	}
	return (0);
}

// Cree la liste chainee et les thread
int	ft_creation_table(t_struct *jsp)
{
	int				i;
	t_philosophe	*premier;
	t_philosophe	*actuel;
	t_philosophe	*temp;

	i = 0;
	premier = ft_lstnew(i);
	if (!premier)
		return (1);
	actuel = premier;
	if(ft_initialisation(actuel))
		return (1);
	//actuel->fourchette_d = i + 2;
	while (i < jsp->philosophes)
	{
		if (i != 0)
		{
			actuel = ft_lstadd_back(&premier, ft_lstnew(i));
			if (!actuel)
				return (1);
			if(ft_initialisation(actuel))
				return (1);
			actuel->fourchette_g = &temp->fourchette_d;
			//actuel->fourchette_d = i + 2;
		}
		actuel->i = i;
		actuel->philo = i;
		temp = actuel;
		i++;
	}
	if (i >= 2)
		premier->fourchette_g = &actuel->fourchette_d;
	if (ft_thread_philo(&premier))
		return (ft_vide_liste(&premier));
	ft_vide_liste(&premier);
	printf("parfait\n");
	return (0);
}
