/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 06:02:03 by ilselbon          #+#    #+#             */
/*   Updated: 2023/07/12 18:00:21 by ilona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_sleep(t_philosophe *actuel)
{
	if (ft_print(actuel, "is sleeping		🛌", 0))
		return (1);
	ft_usleep(actuel->info->tts, actuel);
	actuel->sdk = 1;
	return (0);
}
