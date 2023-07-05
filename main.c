/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilselbon <ilselbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 22:10:37 by ilselbon          #+#    #+#             */
/*   Updated: 2023/06/23 19:28:04 by ilselbon         ###   ########.fr       */
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

int	main(int ac, char **av)
{
	t_struct	ma_structure;

	gettimeofday(&ma_structure.info.debut, NULL);
	//veirifie les nombre d'arguments entrés
	if (ac > 6)
		printf("trop d'arguments\n");
	else if (ac < 5)
		printf("pas assez d'arguments\n");
	else if (ac == 6 || ac == 5)
	{
		ma_structure.info.ac = ac;
		//verifie la validité des arguments grace a la fonction "ft_verif_args"
		if (!ft_verif_args(ac, av, &ma_structure.info))
		{
			//creation de la liste chainee et initialisation des structures
			if (ft_creation_table(&ma_structure))
				printf("erreur\n");
		}
	}
	return (0);
}