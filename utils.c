/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilselbon <ilselbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 19:55:16 by ilselbon          #+#    #+#             */
/*   Updated: 2023/06/23 21:20:56 by ilselbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned long	ft_time2(struct timeval debut)
{
	struct timeval	rn;
	
	gettimeofday(&rn, NULL);
	return (rn.tv_usec - debut.tv_usec);
}

void	ft_usleep(int tmp)
{
	long debut;
	long actuel;
 	struct timeval deb;

 	gettimeofday(&deb, NULL);
	debut = ft_time2(deb);
	actuel = debut;
	while(tmp > (actuel - debut))
		actuel = ft_time2(deb);
}