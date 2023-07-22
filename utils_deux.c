/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_deux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilselbon <ilselbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 13:24:03 by ilona             #+#    #+#             */
/*   Updated: 2023/07/23 00:59:03 by ilselbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Détruit tous les mutex
void	ft_destroy(t_struct *m_s)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&m_s->info.m_ate);
	pthread_mutex_destroy(&m_s->info.m_stop);
	pthread_mutex_destroy(&m_s->info.m_printf);
	pthread_mutex_destroy(&m_s->info.mutex_mort);
	if (m_s->tab)
	{
		while (i < m_s->info.nb_de_philos)
		{
			pthread_mutex_destroy(&m_s->tab[i].m_tod);
			pthread_mutex_destroy(&m_s->tab[i].mutex);
			pthread_mutex_destroy(&m_s->tab[i].fourchette_d);
			i++;
		}
		free(m_s->tab);
	}
}

