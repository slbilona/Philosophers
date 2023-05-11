/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creation_thread.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilselbon <ilselbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 22:10:30 by ilselbon          #+#    #+#             */
/*   Updated: 2023/05/11 22:54:26 by ilselbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int ft_verif_philos(t_struct *jsp)
{
	t_philosophe *actuel;
	actuel = jsp->philosophe;
	t_info info;

	info = jsp->info;
	//verifier si un philosophe est mort
	while(actuel)
	{
		//verifier si chaque philo a mange le nombre minimal de fois
		if(actuel->nb_de_repas < info.notepme)
			return 1;
		actuel = actuel->next;
	}
	return (0);
}

void	*ft_philo(void *jsp)
{
	t_struct		*je_sais_pas;
	t_philosophe	*actuel;

	je_sais_pas = (t_struct *) jsp;
	actuel = je_sais_pas->philosophe;
//trouver le bon actuel grace a l'index
	while (je_sais_pas->index != actuel->i)
		actuel = actuel->next;
	while (ft_verif_philos(jsp))
	{
		if (actuel->sdk == 3)
		{
			pthread_mutex_lock(&actuel->fourchette_d);
			printf("le philosophe numero %d a pris une fouchette droite\n", actuel->i);
			pthread_mutex_lock(actuel->fourchette_g);
			printf("le philosophe numero %d a pris une fouchette gauche\n", actuel->i);
			printf("le philosophe %d mange\n", actuel->i);
			actuel->nb_de_repas++;
			printf("le philosophe numero %d a mange %d fois\n", actuel->i, actuel->nb_de_repas);
			usleep(50);
			pthread_mutex_unlock(&actuel->fourchette_d);
			pthread_mutex_unlock(actuel->fourchette_g);
			actuel->sdk = 1;
		}
		else if (actuel->sdk == 1)
		{
			printf("le philosophe numero %d dort\n", actuel->i);
			usleep(50);
			actuel->sdk = 2;
		}
		else if (actuel->sdk == 2)
		{
			printf("le philosophe numero %d pense\n", actuel->i);
			actuel->sdk = 3;
		}
	}
	return (NULL);
}

/*
0 : rien
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
	int				j;

	premier = &jsp->philosophe;
	i = 0;
	actuel = *premier;
	j = 2;
	while(j)
	{
		while (actuel)
		{
			printf("actuel->i : %d\n", actuel->i);
			jsp->index = actuel->i;
			if(j == 2)
			{
				if (actuel->i % 2 == 0)
				{
					if (pthread_create(&actuel->philo, NULL, ft_philo, (void *)jsp))
					{
						printf("la creation du thread numero %d a echouee\n", i);
						return (1);
					}
				}
			}
			if (j == 1)
			{
				if (actuel->i % 2 != 0)
				{
					if (pthread_create(&actuel->philo, NULL, ft_philo, (void *)jsp))
					{
						printf("la creation du thread numero %d a echouee\n", i);
						return (1);
					}
				}
			}
			i++;
			usleep(100);
			actuel = actuel->next;
		}
		j--;
	}
	actuel = *premier;
	while (actuel)
	{
		if (pthread_join(actuel->philo, NULL))
		{
			printf("le join numero %d a echoue\n", i);
			return (1);
		}
		actuel = actuel->next;
	}
	return (0);
}

void	ft_jsp(t_philosophe **premier)
{
	t_philosophe	*numero_un;
	t_philosophe	*dernier;

	numero_un = *premier;
	dernier = *premier;
	while (dernier->next)
		dernier = dernier->next;
	numero_un->fourchette_g = &dernier->fourchette_d;
}

// Cree la liste chainee et les thread
int	ft_creation_table(t_struct *jsp)
{
	t_philosophe	*actuel;
	t_philosophe	*temp;
	t_philosophe	*vide;
	int				i;

	i = 0;
	jsp->philosophe = ft_lstnew(i);
	if (!jsp->philosophe)
		return (1);
	actuel = jsp->philosophe;
	if (ft_initialisation(actuel))
		return (1);
	while (i < jsp->info.philosophes)
	{
		if (i != 0)
		{
			actuel = ft_lstadd_back(&jsp->philosophe, ft_lstnew(i));
			if (!actuel)
				return (1);
			if (ft_initialisation(actuel))
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
	vide = jsp->philosophe;
	while (vide)
	{
		pthread_mutex_destroy(&vide->fourchette_d);
		vide = vide->next;
	}
	printf("parfait\n");
	return (0);
}
