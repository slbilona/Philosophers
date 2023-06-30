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
int	ft_verif_args(int ac, char **av, t_info *jsp)
{
	if (!ft_chiffres(av, 1, 0))
		return (printf("Erreur : les arguments doivent etre des nombres\n"), 1);
	jsp->philosophes = ft_atoi(av[1]);
	jsp->ttd = ft_atoi(av[2]);
	jsp->tte = ft_atoi(av[3]);
	jsp->tts = ft_atoi(av[4]);
	if (ac == 6)
	{
		jsp->notepme = ft_atoi(av[5]);
		if (jsp->notepme < 0)
			return (printf("Erreur : aucun argument ne peut etre inferieur a 0.\n"), 1);
	}
	if (jsp->philosophes < 0 || jsp->ttd < 0 || jsp->tte < 0 || jsp->tts < 0)
		return (printf("Erreur : aucun argument ne peut etre inferieur a 0.\n"), 1);
	else if (jsp->philosophes > 1024)
		return (printf("Erreur : il ne peut y avoir plus de 1024 philosophes.\n"), 1);
	else if (jsp->philosophes == 0)
		return (printf("Erreur : il n'y a pas de philosophes\n"), 1);
	return (0);
}
