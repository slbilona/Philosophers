/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 22:10:32 by ilselbon          #+#    #+#             */
/*   Updated: 2023/07/12 11:57:56 by ilona            ###   ########.fr       */
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

// Initialise la structure info
void	ft_init_info(char **av, t_info *info)
{
	gettimeofday(&info->debut, NULL);
	info->nb_de_philos = ft_atoi(av[1]);
	info->ttd = ft_atoi(av[2]);
	info->tte = ft_atoi(av[3]);
	info->tts = ft_atoi(av[4]);
	info->i_mort = 1;
	pthread_mutex_init(&info->mutex_mort, NULL);
	pthread_mutex_init(&info->m_printf, NULL);
}

// Vérifie si les arguments entrés sont valides.
int	ft_verif_args(int ac, char **av, t_info *info)
{
	if (!ft_chiffres(av, 1, 0))
		return (printf("Erreur : les arguments doivent etre des nombres\n"), 1);
	ft_init_info(av, info);
	if (ac == 6)
	{
		info->notepme = ft_atoi(av[5]);
		if (info->notepme < 0)
			return (printf("Erreur : aucun argument ne peut etre inferieur a 0.\n"), 1);
	}
	else
		info->notepme = -1;
	if (info->nb_de_philos < 0 || info->ttd < 0 || info->tte < 0 || info->tts < 0)
		return (printf("Erreur : aucun argument ne peut etre inferieur a 0.\n"), 1);
	else if (info->nb_de_philos > 1024)
		return (printf("Erreur : il ne peut pas y avoir plus de 1024 philosophes.\n"), 1);
	else if (info->nb_de_philos == 0)
		return (printf("Erreur : il n'y a pas de philosophes\n"), 1);
	return (0);
}
