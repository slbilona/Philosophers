/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilselbon <ilselbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 02:33:46 by ilselbon          #+#    #+#             */
/*   Updated: 2023/07/11 04:37:45 by ilselbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"



void check_death(t_struct *ma_structure)
{
	int i;

	while(1)
	{
		i = 0;
		while(i < ma_structure->info.nb_de_philos)
		{
			if (ft_mort(ma_structure->tab))
				return ;
			i++;
		}
	}
}