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

void	ft_usleep(int tmp, struct timeval deb)
{
	long debut;
	long actuel;

	debut = ft_time2(deb);
	actuel = debut;
	while(tmp > (actuel - debut))
	{
		usleep(10);
		actuel = ft_time2(deb);
		//printf("actuel - debut : %ld; actuel : %ld\n", (actuel - debut), actuel);
	}
}

int main()
{
	struct timeval debut;
	gettimeofday(&debut, NULL);
	printf("debut : %ld\n", ft_time2(debut));
	ft_usleep(100, debut);
	long info = ft_time2(debut);
	printf("%ld\n", info);
}