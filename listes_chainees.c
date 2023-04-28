/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listes_chainees.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilselbon <ilselbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 22:12:42 by ilselbon          #+#    #+#             */
/*   Updated: 2023/04/28 17:09:30 by ilselbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philosophe	*ft_lstnew(int i)
{
	t_philosophe	*new;

	new = malloc(sizeof(t_philosophe));
	if (!new)
		return (NULL);
	new->fourchette_d = 0;
	new->i = i;
	new->next = NULL;
	return (new);
}

t_philosophe	*ft_lstadd_back(t_philosophe **lst, t_philosophe *new)
{
	t_philosophe	*actuel;

	actuel = *lst;
	while (actuel->next)
		actuel = actuel->next;
	actuel->next = new;
	new->next = NULL;
	return (new);
}

void	ft_vide_liste(t_philosophe **pile)
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
}
