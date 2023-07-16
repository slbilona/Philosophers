/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_mort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 05:32:50 by ilselbon          #+#    #+#             */
/*   Updated: 2023/07/16 19:27:08 by ilona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_mort(t_philosophe *actuel)
{
	int				stop;
	long int		tod;

	stop = 0;
	pthread_mutex_lock(&actuel->m_tod);
	tod = actuel->time_of_death;
	pthread_mutex_unlock(&actuel->m_tod);
	if (tod <= ft_time(actuel))
	{
		pthread_mutex_lock(&actuel->info->mutex_mort);
		actuel->info->i_mort = 0;
		pthread_mutex_unlock(&actuel->info->mutex_mort);
		stop = 1;
		pthread_mutex_lock(&actuel->info->m_printf);
		printf(" %ld	%d	died			💀\n", ft_time(actuel), actuel->i);
		pthread_mutex_unlock(&actuel->info->m_printf);
	}
	return (stop);
}

// Verifie si un philo est mort ou si tous les philo ont suffisament mangé
int	ft_verif_philos(t_philosophe *actuel)
{
	int	ret;

	ret = 1;
	pthread_mutex_lock(&actuel->info->mutex_mort);
	ret = actuel->info->i_mort;
	pthread_mutex_unlock(&actuel->info->mutex_mort);
	pthread_mutex_lock(&actuel->info->m_ate);
	if (actuel->info->i_ate == 0 && ret == 1)
		ret = 0;
	pthread_mutex_unlock(&actuel->info->m_ate);
	return (ret);
}

// Verifie si un philo est mort ou si tous les philo ont suffisament mangé
void	check_death(t_struct *m_s)
{
	int	i;
	int	j;

	while (1)
	{
		i = 0;
		j = 0;
		while (i < m_s->info.nb_de_philos)
		{
			pthread_mutex_lock(&m_s->info.m_stop);
			if (ft_mort(&m_s->tab[i]))
			{
				pthread_mutex_unlock(&m_s->info.m_stop);
				return ;
			}
			pthread_mutex_unlock(&m_s->info.m_stop);
			pthread_mutex_lock(&m_s->tab[i].mutex);
			if (m_s->tab[i].i_ate == 1)
				j++;
			pthread_mutex_unlock(&m_s->tab[i].mutex);
			i++;
		}
		if (ft_check_death_deux(m_s, j))
			return ;
	}
}

int	ft_check_death_deux(t_struct *m_s, int j)
{
	if (j == m_s->info.nb_de_philos)
	{
		pthread_mutex_lock(&m_s->info.m_ate);
		m_s->info.i_ate = 0;
		pthread_mutex_unlock(&m_s->info.m_ate);
		return (1);
	}
	return (0);
}
