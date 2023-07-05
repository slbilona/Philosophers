/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creation_thread.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 22:10:30 by ilselbon          #+#    #+#             */
/*   Updated: 2023/07/05 20:26:20 by ilona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//donne le temps en microseconde depuis le debut du programme
unsigned long ft_time(t_struct *ma_structure)
{
	struct timeval rn;
	
	gettimeofday(&rn, NULL);
	return (rn.tv_usec - ma_structure->info.debut.tv_usec);
}

//verifie si aucun philosophe n'est mort
int ft_verif_philos(t_struct *ma_structure)
{
	const t_philosophe *actuel;
	actuel = ma_structure->philosophe;
	t_info info;
	int i = 0;

	info = ma_structure->info;
	//verifier si un philosophe est mort
	// if (pthread_mutex_trylock(&ma_structure->mort) == 0)
	// 	printf("trylock\n");
	// else
	// 	return (0);
	while (actuel)
	{
		if (actuel->vie == 0)
		{
			//printf("BOO !\n");
			return (0);
		}
		//verifier si chaque philo a mange le nombre minimal de fois
		if (actuel->nb_de_repas < info.notepme)
			i++;
		actuel = actuel->next;
	}
	if (i > 0)
		return (1);
	return (0);
}

void	ft_fourchettes_droitier()
{
	pthread_mutex_lock(&actuel->fourchette_d);
	printf("%ld %d has taken a fork\n", ft_time(ma_structure), actuel->i);
	gettimeofday(&temps2, NULL);
	// if((temps2.tv_usec - temps1.tv_usec) > m_s->info.ttd)
	// {
	// 	actuel->vie = 0;
	// 	printf("%ld %d died\n", ft_time(ma_structure), actuel->i);
	// 	return (1);
	// }
	// if(!ft_verif_philos(ma_structure))
	// 	return (1);
	pthread_mutex_lock(actuel->fourchette_g);
	printf("%ld %d has taken a fork\n", ft_time(ma_structure), actuel->i);
	
}

int ft_repas(void *ma_structure, t_philosophe *actuel, struct timeval temps1, struct timeval temps2)
{
	t_struct		*m_s;

	m_s = ma_structure;
	if(!ft_verif_philos(ma_structure))
		return (1);
	ft_fourchettes_droitier();gettimeofday(&temps2, NULL);
	if((temps2.tv_usec - temps1.tv_usec) > m_s->info.ttd)
	{
		actuel->vie = 0;
		printf("%ld %d died\n", ft_time(ma_structure), actuel->i);
		return (1);
	}
	if(!ft_verif_philos(ma_structure))
		return (1);
	printf("%ld %d is eating\n", ft_time(ma_structure), actuel->i);
	actuel->nb_de_repas++;
	//printf("le philosophe numero %d a mange %d fois\n", actuel->i, actuel->nb_de_repas);
	ft_usleep(m_s->info.tte);
	gettimeofday(&temps1, NULL);
	pthread_mutex_unlock(actuel->fourchette_g);
	pthread_mutex_unlock(&actuel->fourchette_d);
	actuel->sdk = 1;
	return (0);
}

void	*ft_philo(void *ma_structure)
{
	t_struct		*m_s;
	t_philosophe	*actuel;
	struct timeval temps1;
	struct timeval temps2;

	m_s = (t_struct *) ma_structure;
	actuel = m_s->philosophe;
	//trouver le bon actuel grace a l'index
	//printf("ma_structure index : %d, actuel->i .%d\n", m_s->index, actuel->i);
	while (actuel->i != m_s->index)
		actuel = actuel->next;
	temps1.tv_usec = m_s->info.debut.tv_usec;
	printf("thread numero %d s'est lancé\n", actuel->i);
	while (ft_verif_philos(ma_structure) == 1)
	{
		//prends le temps du debut de la boucle
		gettimeofday(&temps2, NULL);
		if((temps2.tv_usec - temps1.tv_usec) > m_s->info.ttd)
		{
			actuel->vie = 0;
			printf("%ld %d died1 \n", ft_time(ma_structure), actuel->i);
			return (NULL);
		}
		if (actuel->sdk == 3)
		{
			if(ft_repas(ma_structure, actuel, temps1, temps2))
				return (NULL);
		}
		else if (actuel->sdk == 1 && ft_verif_philos(ma_structure))
		{
			printf("%ld %d is sleeping\n", ft_time(ma_structure), actuel->i);
			//printf("tts : %d\n\n", m_s->info.tts);
			ft_usleep(m_s->info.tts);
			actuel->sdk = 2;
		}
		else if (actuel->sdk == 2 && ft_verif_philos(ma_structure))
		{
			printf("%ld %d is thinking\n", ft_time(ma_structure), actuel->i);
			ft_usleep(10);
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
		actuel->vie = 1;
		actuel->fourchette_g = NULL;
		pthread_mutex_init(&actuel->fourchette_d, NULL);
		actuel->philo = 0;
		actuel->next = NULL;
		actuel->sdk = 3;
		actuel->nb_de_repas = 0;
	}
	return (0);
}

//POUR REMPLACER LA FONCTION JUSTE EN DESSOUS MAIS FONCTIONNE PAS ENCORE 
int	test_lancement_thread(t_struct *ma_structure)
{
	t_philosophe *actuel;
	t_philosophe **premier;
	int j;

	j = 2;
	premier = &ma_structure->philosophe;
	while(j)
	{
		if (j == 2)
			actuel = *premier;
		else
		{
			actuel = *premier;
			actuel = actuel->next;
		}
		while(actuel)
		{
			//printf("%d\n", actuel->i);
			ma_structure->index = actuel->i;
			if (pthread_create(&actuel->philo, NULL, ft_philo, (void *)ma_structure))
			{
				printf("la creation du thread numero %d a echouee\n", actuel->i);
				return (1);
			}
			ft_usleep(50);
			if(actuel->next)
				actuel = actuel->next->next;
			else
				actuel = actuel->next;
		}
		j--;
	}
	actuel = *premier;
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

// initialise autant de thread qu'il y a de philosophes
int	ft_thread_philo(t_struct *ma_structure)
{
	t_philosophe	**premier;
	t_philosophe	*actuel;
	int				j;

	premier = &ma_structure->philosophe;
	j = 2;
	while(j)
	{
		actuel = *premier;
		while (actuel)
		{
			ma_structure->index = actuel->i;
			if(j == 2)
			{
				if (actuel->i % 2 != 0)
				{
					printf("actuel->i : %d\n", actuel->i);
					if (pthread_create(&actuel->philo, NULL, ft_philo, (void *)ma_structure))
					{
						printf("la creation du thread numero %d a echouee\n", actuel->i);
						return (1);
					}
					ft_usleep(10);
				}
			}
			if (j == 1)
			{
				if (actuel->i % 2 == 0)
				{
					printf("actuel->i : %d\n", actuel->i);
					if (pthread_create(&actuel->philo, NULL, ft_philo, (void *)ma_structure))
					{
						printf("la creation du thread numero %d a echouee\n", actuel->i);
						return (1);
					}
					ft_usleep(10);
				}
			}
			actuel = actuel->next;
		}
		j--;
	}
	actuel = *premier;
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

void	ft_premiere_fouchette_gauche(t_philosophe **premier)
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
int	ft_creation_table(t_struct *ma_structure)
{
	t_philosophe	*actuel;
	t_philosophe	*temp;
	int				i;

	i = 0;
	ma_structure->philosophe = ft_lstnew(i); // creation du premier philosophe
	if (!ma_structure->philosophe)
		return (1);
	actuel = ma_structure->philosophe;
	if (ft_initialisation(actuel)) //initialisation du premier philosophe
	 	return (1);
	// boucle de creation de tous les philosophes dans la liste chainee
	while (i < ma_structure->info.philosophes)
	{
		if (i != 0)
		{
			actuel = ft_lstadd_back(&ma_structure->philosophe, ft_lstnew(i));
			if (!actuel)
				return (1);
			if (ft_initialisation(actuel))
				return (1);
			actuel->fourchette_g = &temp->fourchette_d;
		}
		actuel->i = i + 1;
		actuel->philo = i;
		temp = actuel;
		i++;
	}
	if (i >= 1)
		ma_structure->philosophe->fourchette_g = &actuel->fourchette_d;
	if (test_lancement_thread(ma_structure))
		return (ft_vide_liste(&ma_structure->philosophe));
	ft_vide_liste(&ma_structure->philosophe);
	printf("parfait\n");
	return (0);
}
