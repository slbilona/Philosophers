/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listes_chainees.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilselbon <ilselbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 22:12:42 by ilselbon          #+#    #+#             */
/*   Updated: 2023/05/05 20:45:16 by ilselbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philosophe	*ft_lstnew(int i)
{
	t_philosophe	*new;

	new = malloc(sizeof(t_philosophe));
	if (!new)
		return (NULL);
	// new->fourchette_d = 0;
	pthread_mutex_init(&new->fourchette_d, NULL);
	new->i = i;
	new->next = NULL;
	return (new);
}

// ajoute un maillon a la fin de la liste chainee
t_philosophe	*ft_lstadd_back(t_philosophe **lst, t_philosophe *new)
{
	t_philosophe	*actuel;

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

int	ft_vide_liste(t_philosophe **pile)
{
	t_philosophe	*actuel;
	t_philosophe	*temp;

	actuel = *pile;
	while (actuel)
	{
		temp = actuel;
		actuel = actuel->next;
		free(temp);
	}
	return (1);
}
