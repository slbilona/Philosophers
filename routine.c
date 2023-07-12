/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 06:02:03 by ilselbon          #+#    #+#             */
/*   Updated: 2023/07/12 11:09:05 by ilona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_sleep(t_philosophe *actuel)
{
	if(ft_print(actuel, "is sleeping", 0))
		return (1);
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
	actuel->sdk = 3;
	return (0);
}
