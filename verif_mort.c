/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_mort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 05:32:50 by ilselbon          #+#    #+#             */
/*   Updated: 2023/07/15 17:50:39 by ilona            ###   ########.fr       */
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
		//pthread_mutex_lock(&actuel->info->m_stop);
		stop = 1;
		//pthread_mutex_unlock(&actuel->info->m_stop);
		pthread_mutex_lock(&actuel->info->m_printf);
		printf(" %ld	%d	died			💀\n", ft_time(actuel), actuel->i);
		pthread_mutex_unlock(&actuel->info->m_printf);
	}
	return (stop);
}

int	ft_verif_philos(t_philosophe *actuel)
{
	int	ret;

	ret = 1;
	pthread_mutex_lock(&actuel->info->mutex_mort);
	ret = actuel->info->i_mort;
	pthread_mutex_unlock(&actuel->info->mutex_mort);
	return (ret);
}

void	check_death(t_struct *ma_structure)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < ma_structure->info.nb_de_philos)
		{
			pthread_mutex_lock(&ma_structure->info.m_stop);
			if (ft_mort(&ma_structure->tab[i]))
			{
				pthread_mutex_unlock(&ma_structure->info.m_stop);
				return ;
			}
			pthread_mutex_unlock(&ma_structure->info.m_stop);
			i++;
		}
	}
}
