/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilselbon <ilselbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 22:10:32 by ilselbon          #+#    #+#             */
/*   Updated: 2023/05/09 19:12:47 by ilselbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Vérifie si le char qui lui est envoyé est un chiffre.
int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

// Vérifie s'il n'y a que des chiffres entrés en arguments.
int	ft_chiffres(char **av, int j, int i)
{
	int	o;

	j = 1;
	while (av[j])
	{
		i = 0;
		while (av[j][i])
		{
			o = 0;
			while (av[j][i] == ' ' && av[j][i] != '\0')
				i++;
			if ((av[j][i] == '-' || av[j][i] == '+') && av[j][i] != '\0')
			{
				i++;
				o++;
			}
			while ((ft_isdigit(av[j][i]) == 1) && av[j][i++] != '\0')
				o--;
			if (((ft_isdigit(av[j][i]) == 0 && av[j][i] != ' ')
					&& av[j][i] != '\0') || o > 0)
				return (0);
		}
		j++;
	}
	return (1);
}

// Vérifie si les arguments entrés sont valides.
int	ft_verif_args(int ac, char **av, t_info *ma_structure)
{
	if (!ft_chiffres(av, 1, 0))
		return (printf("Erreur : les arguments doivent etre des nombres\n"), 1);
	ma_structure->philosophes = ft_atoi(av[1]);
	ma_structure->ttd = ft_atoi(av[2]);
	ma_structure->tte = ft_atoi(av[3]);
	ma_structure->tts = ft_atoi(av[4]);
	if (ac == 6)
	{
		ma_structure->notepme = ft_atoi(av[5]);
		if (ma_structure->notepme < 0)
			return (printf("Erreur : aucun argument ne peut etre inferieur a 0.\n"), 1);
	}
	if (ma_structure->philosophes < 0 || ma_structure->ttd < 0 || ma_structure->tte < 0 || ma_structure->tts < 0)
		return (printf("Erreur : aucun argument ne peut etre inferieur a 0.\n"), 1);
	else if (ma_structure->philosophes > 1024)
		return (printf("Erreur : il ne peut y avoir plus de 1024 philosophes.\n"), 1);
	else if (ma_structure->philosophes == 0)
		return (printf("Erreur : il n'y a pas de philosophes\n"), 1);
	return (0);
}
