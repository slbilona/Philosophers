/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilselbon <ilselbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 06:02:03 by ilselbon          #+#    #+#             */
/*   Updated: 2023/07/11 06:02:10 by ilselbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_sleep(t_philosophe *actuel)
{
	pthread_mutex_lock(&actuel->info->m_printf);
	if (!ft_verif_philos(actuel))
	{
		pthread_mutex_unlock(&actuel->info->m_printf);
		return (1);
	}
	printf("%ld %d is sleeping\n", ft_time(actuel), actuel->i);
	pthread_mutex_unlock(&actuel->info->m_printf);
	ft_usleep(actuel->info->tts, actuel);
	actuel->sdk = 1;
	return (0);
}

int	ft_think(t_philosophe *actuel)
{
	pthread_mutex_lock(&actuel->info->m_printf);
	if (!ft_verif_philos(actuel))
	{
		pthread_mutex_unlock(&actuel->info->m_printf);
		return (1);
	}
	printf("%ld %d is thinking\n", ft_time(actuel), actuel->i);
	pthread_mutex_unlock(&actuel->info->m_printf);
	ft_usleep(5, actuel);
	actuel->sdk = 3;
	return (0);
}
