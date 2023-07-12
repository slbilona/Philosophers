/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_mort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 05:32:50 by ilselbon          #+#    #+#             */
/*   Updated: 2023/07/12 11:14:49 by ilona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_mort(t_philosophe actuel)
{
	int				stop;
	long int		tod;

	stop = 0;
	pthread_mutex_lock(&actuel.mutex);
	tod = actuel.time_of_death;
	pthread_mutex_unlock(&actuel.mutex);
	if (tod <= ft_time(&actuel))
	{
		pthread_mutex_lock(&actuel.info->mutex_mort);
		actuel.info->i_mort = 0;
		stop = 1;
		pthread_mutex_unlock(&actuel.info->mutex_mort);
		pthread_mutex_lock(&actuel.info->m_printf);
		printf("%ld %d died\n", ft_time(&actuel), actuel.i);
		pthread_mutex_unlock(&actuel.info->m_printf);
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
			if (ft_mort(ma_structure->tab[i]))
				return ;
			i++;
		}
	}
}
