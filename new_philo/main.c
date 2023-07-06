/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 12:32:52 by ilona             #+#    #+#             */
/*   Updated: 2023/07/06 19:21:29 by ilona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_struct	ma_structure;

	gettimeofday(&ma_structure.info.debut, NULL);
	if (ac > 6)
		printf("trop d'arguments\n");
	else if (ac < 5)
		printf("pas assez d'arguments\n");
	else if (ac == 6 || ac == 5)
	{
		if (!ft_verif_args(ac, av, &ma_structure.info))
		{
			if (ft_creation_table(&ma_structure))
				printf("erreur\n");
		}
	}
	return (0);
}
