/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listes_chainees.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 22:12:42 by ilselbon          #+#    #+#             */
/*   Updated: 2023/07/06 18:28:55 by ilona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philosophe	*ft_lstnew(int i)
{
	t_philosophe	*new;

	new = malloc(sizeof(t_philosophe));
	if (!new)
		return (NULL);
	if (pthread_mutex_init(&new->fourchette_d, NULL) != 0)
		return (free(new), NULL);
	new->i = i + 1;
	new->philo = i;
	new->vie = 1;
	new->fourchette_g = NULL;
	new->sdk = 3;
	new->nb_de_repas = 0;
	new->next = NULL;
	return (new);
}

// ajoute un maillon a la fin de la liste chainee
t_philosophe	*ft_lstadd_back(t_philosophe **lst, t_philosophe *new)
{
	t_philosophe	*actuel;

	if (!*lst && new)
	{
		*lst = new;
		return (new);
	}
	if (new)
	{
		actuel = *lst;
		while (actuel->next)
			actuel = actuel->next;
		actuel->next = new;
		new->next = NULL;
		return (new);
	}
	return (NULL);
}

void	ft_vide_liste(t_struct *m_s)
{
	t_philosophe	*actuel;
	t_philosophe	*temp;

	printf("ft_vide_liste\n");
	actuel = m_s->philosophe;
	while (actuel)
	{
		temp = actuel;
		pthread_mutex_destroy(&temp->fourchette_d);
		actuel = actuel->next;
		free(temp);
	}
	pthread_mutex_destroy(&m_s->info.mutex_mort);
}
