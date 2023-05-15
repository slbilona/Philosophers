/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creation_thread.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilselbon <ilselbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 22:10:30 by ilselbon          #+#    #+#             */
/*   Updated: 2023/05/15 22:51:31 by ilselbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned long ft_time(t_struct *jsp)
{
	struct timeval rn;
	
	gettimeofday(&rn, NULL);
	return (rn.tv_usec - jsp->info.debut.tv_usec);
}

//verifie si aucun philosophe n'est mort
int ft_verif_philos(t_struct *jsp)
{
	const t_philosophe *actuel;
	actuel = jsp->philosophe;
	t_info info;

	info = jsp->info;
	//verifier si un philosophe est mort
	while(actuel)
	{
		//verifier si chaque philo a mange le nombre minimal de fois
		if(actuel->nb_de_repas < info.notepme)
			return 1;
		if(actuel->vie == 0)
		{
			printf("BOO !\n");
			return (0);
		}
		actuel = actuel->next;
	}
	return (0);
}

void	*ft_philo(void *jsp)
{
	t_struct		*je_sais_pas;
	t_philosophe	*actuel;
	struct timeval temps1;
	struct timeval temps2;

	je_sais_pas = (t_struct *) jsp;
	actuel = je_sais_pas->philosophe;
//trouver le bon actuel grace a l'index
	while (je_sais_pas->index != actuel->i)
		actuel = actuel->next;
	temps1.tv_usec = je_sais_pas->info.debut.tv_usec;
	while (ft_verif_philos(jsp) == 1)
	{
		gettimeofday(&temps2, NULL);
		if((temps2.tv_usec - temps1.tv_usec) > je_sais_pas->info.ttd)
		{
			printf("%ld %d died\n", ft_time(jsp), actuel->i);
			actuel->vie = 0;
			break;
		}
		if (actuel->sdk == 3)
		{
			pthread_mutex_lock(&actuel->fourchette_d);
			printf("%ld %d has taken a fork (droite)\n", ft_time(jsp), actuel->i);
			gettimeofday(&temps2, NULL);
			if((temps2.tv_usec - temps1.tv_usec) > je_sais_pas->info.ttd)
			{
				printf("%ld %d died\n", ft_time(jsp), actuel->i);
				actuel->vie = 0;
				break;
			}
			pthread_mutex_lock(actuel->fourchette_g);
			printf("%ld %d has taken a fork (gauche)\n", ft_time(jsp), actuel->i);
			gettimeofday(&temps2, NULL);
			if((temps2.tv_usec - temps1.tv_usec) > je_sais_pas->info.ttd)
			{
				printf("%ld %d died\n", ft_time(jsp), actuel->i);
				actuel->vie = 0;
				break;
			}
			else if (ft_verif_philos(jsp))
			{
				printf("%ld %d is eating\n", ft_time(jsp), actuel->i);
				actuel->nb_de_repas++;
				//printf("le philosophe numero %d a mange %d fois\n", actuel->i, actuel->nb_de_repas);
				usleep(je_sais_pas->info.tte);
				gettimeofday(&temps1, NULL);
				pthread_mutex_unlock(actuel->fourchette_g);
				pthread_mutex_unlock(&actuel->fourchette_d);
				actuel->sdk = 1;
			}
		}
		else if (actuel->sdk == 1)
		{
			printf("%ld %d is sleeping\n", ft_time(jsp), actuel->i);
			usleep(je_sais_pas->info.tts);
			actuel->sdk = 2;
		}
		else if (actuel->sdk == 2)
		{
			printf("%ld %d is thinking\n", ft_time(jsp), actuel->i);
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
	int				j;

	premier = &jsp->philosophe;
	j = 2;
	while(j)
	{
		actuel = *premier;
		while (actuel)
		{
			jsp->index = actuel->i;
			if(j == 2)
			{
				if (actuel->i % 2 != 0)
				{
					//printf("actuel->i : %d\n", actuel->i);
					if (pthread_create(&actuel->philo, NULL, ft_philo, (void *)jsp))
					{
						printf("la creation du thread numero %d a echouee\n", actuel->i);
						return (1);
					}
					usleep(100);
				}
			}
			if (j == 1)
			{
				if (actuel->i % 2 == 0)
				{
					//printf("actuel->i : %d\n", actuel->i);
					if (pthread_create(&actuel->philo, NULL, ft_philo, (void *)jsp))
					{
						printf("la creation du thread numero %d a echouee\n", actuel->i);
						return (1);
					}
					usleep(100);
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
		actuel->i = i + 1;
		actuel->philo = i;
		temp = actuel;
		i++;
	}
	if (i >= 1)
		jsp->philosophe->fourchette_g = &actuel->fourchette_d;
	if (ft_thread_philo(jsp))
		return (ft_vide_liste(&jsp->philosophe));
	ft_vide_liste(&jsp->philosophe);
	printf("parfait\n");
	return (0);
}
