/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 12:34:56 by ilona             #+#    #+#             */
/*   Updated: 2023/07/06 13:21:26 by ilona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//transforme une string en int
int	ft_atoi(const char *nptr)
{
	int	result;
	int	i;
	int	sign;

	sign = 1;
	i = 0;
	result = 0;
	while ((9 <= nptr[i] && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + nptr[i] - 48;
		i++;
	}
	return (result * sign);
}

// Donne le temps en micro-seconde depuis le lancement du programme
unsigned long	ft_time(t_struct *ma_structure)
{
	struct timeval	rn;

	gettimeofday(&rn, NULL);
	return (rn.tv_usec - ma_structure->info.debut.tv_usec);
}

unsigned long	ft_time2(struct timeval debut)
{
	struct timeval	rn;

	gettimeofday(&rn, NULL);
	return (rn.tv_usec - debut.tv_usec);
}

void	ft_usleep(int tmp)
{
	long			debut;
	long			actuel;
	struct timeval	deb;

	gettimeofday(&deb, NULL);
	debut = ft_time2(deb);
	actuel = debut;
	while (tmp > (actuel - debut))
		actuel = ft_time2(deb);
}
