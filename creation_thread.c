/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creation_thread.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilselbon <ilselbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 22:10:30 by ilselbon          #+#    #+#             */
/*   Updated: 2023/05/11 15:22:45 by ilselbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// int ft_verif_mort(t_philosophe *actuel)
// {
	
// 	return (1);
// }

void	*ft_philo(void *jsp)
{
	t_struct *je_sais_pas = (t_struct*) jsp;
	t_philosophe *actuel = je_sais_pas->philosophe;

//trouver le bon actuel grace a l'index
	while(je_sais_pas->index != actuel->i)
		actuel = actuel->next;
	while(1)
	{
		if(actuel->sdk == 3)
		{
			pthread_mutex_lock(&actuel->fourchette_d);
			printf("le philosophe numero %d a pris une fouchette droite\n", actuel->i);
			pthread_mutex_lock(actuel->fourchette_g);
			printf("le philosophe numero %d a pris une fouchette gauche\n", actuel->i);
			printf("le philosophe %d mange\n", actuel->i);
			actuel->nb_de_repas++;
			usleep(50);
			pthread_mutex_unlock(&actuel->fourchette_d);
			pthread_mutex_unlock(actuel->fourchette_g);
			actuel->sdk = 1;
		}
		if(actuel->sdk == 1)
		{
			printf("le philosophe numero %d dort\n", actuel->i);
			usleep(50);
			actuel->sdk = 2;
		}
		if(actuel->sdk == 2)
		{
			printf("le philosophe numero %d pense\n", actuel->i);
			actuel->sdk = 3;
		}
	}
	printf("le philosophe numero %d a mange %d fois\n", actuel->i, actuel->nb_de_repas);
	return (NULL);
}

/*
1 : viens de manger et doit dormir
2 : a dormit et pense en attendant de manger
3 :	att de manger
*/

// initialise chaque maillon de la liste chainee
int	ft_initialisation(t_philosophe *actuel)
{
	if (actuel)
	{
		actuel->i = 0;
		actuel->fourchette_g = NULL;
		pthread_mutex_init(&actuel->fourchette_d, NULL);
		actuel->nb_de_repas = 0;
		actuel->philo = 0;
		actuel->next = NULL;
		actuel->sdk = 3;
	}
	return (0);
}

// initialise autant de thread qu'il y a de philosophes
int	ft_thread_philo(t_struct *jsp)
{
	t_philosophe	**premier;
	t_philosophe	*actuel;
	int				i;

	premier = &jsp->philosophe;
	i = 0;
	actuel = *premier;
	while (actuel)
	{
		printf("actuel->i : %d\n", actuel->i);
		jsp->index = actuel->i;
		if (pthread_create(&actuel->philo, NULL, ft_philo, (void *)jsp))
		{
			printf("la creation du thread numero %d a echouee\n", i);
			return (1);
		}
		// if (pthread_join(actuel->philo, NULL))
		// {
		// 	printf("le join numero %d a echoue\n", i);
		// 	return (1);
		// }
		actuel = actuel->next;
		i++;
		usleep(100);
	}
	return (0);
}

void ft_jsp(t_philosophe **premier)
{
	t_philosophe *numero_un = *premier;
	t_philosophe *dernier = *premier;
	
	
	while(dernier->next)
		dernier = dernier->next;
	numero_un->fourchette_g = &dernier->fourchette_d;

}

// Cree la liste chainee et les thread
int	ft_creation_table(t_struct *jsp)
{
	t_philosophe	*actuel;
	t_philosophe	*temp;
	int				i;

	i = 0;
	jsp->philosophe = ft_lstnew(i);
	if (!jsp->philosophe)
		return (1);
	actuel = jsp->philosophe;
	if(ft_initialisation(actuel))
		return (1);
	while (i < jsp->info.philosophes)
	{
		if (i != 0)
		{
			actuel = ft_lstadd_back(&jsp->philosophe, ft_lstnew(i));
			if (!actuel)
				return (1);
			if(ft_initialisation(actuel))
				return (1);
			actuel->fourchette_g = &temp->fourchette_d;
		}
		actuel->i = i;
		actuel->philo = i;
		temp = actuel;
		i++;
	}
	if (i >= 1)
		jsp->philosophe->fourchette_g = &actuel->fourchette_d;
	if (ft_thread_philo(jsp))
		return (ft_vide_liste(&jsp->philosophe));
	ft_vide_liste(&jsp->philosophe);
	t_philosophe *vide = jsp->philosophe;
	while(vide)
	{
		pthread_mutex_destroy(&vide->fourchette_d);
		vide = vide->next;
	}
	printf("parfait\n");
	return (0);
}
