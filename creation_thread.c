/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creation_thread.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 12:32:25 by ilona             #+#    #+#             */
/*   Updated: 2023/07/16 13:07:19 by ilona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_init_tab(t_struct *ma_structure)
{
	int	i;

	i = 0;
	while (i < ma_structure->info.nb_de_philos)
	{
		pthread_mutex_init(&ma_structure->tab[i].m_tod, NULL);
		pthread_mutex_init(&ma_structure->tab[i].mutex, NULL);
		pthread_mutex_init(&ma_structure->tab[i].fourchette_d, NULL);
		ma_structure->tab[i].i = i + 1;
		ma_structure->tab[i].vie = 0;
		ma_structure->tab[i].sdk = 3;
		ma_structure->tab[i].nb_de_repas = 0;
		ma_structure->tab[i].fourchette_g = NULL;
		ma_structure->tab[i].philo = i;
		ma_structure->tab[i].ate = 0;
		ma_structure->tab[i].info = &ma_structure->info;
		pthread_mutex_lock(&ma_structure->tab[i].mutex);
		ma_structure->tab[i].time_of_death = ma_structure->info.ttd;
		pthread_mutex_unlock(&ma_structure->tab[i].mutex);
		i++;
	}
}

int	ft_creation_table(t_struct *m_s)
{
	int	i;

	i = 0;
	m_s->tab = malloc(sizeof(t_philosophe) * m_s->info.nb_de_philos);
	if (!m_s->tab)
		return (1);
	ft_init_tab(m_s);
	i = m_s->info.nb_de_philos - 1;
	while (i >= 0)
	{
		if (i != 0)
			m_s->tab[i].fourchette_g = &m_s->tab[i - 1].fourchette_d;
		else
			m_s->tab[i].fourchette_g
				= &m_s->tab[m_s->info.nb_de_philos - 1].fourchette_d;
		i--;
	}
	ft_lancement_thread(m_s);
	ft_destroy(m_s);
	return (0);
}

//	Lance chaque threads 
int	ft_lancement_thread(t_struct *m_s)
{
	int	i;

	i = 0;
	while (i < m_s->info.nb_de_philos)
	{
		if (pthread_create(&m_s->tab[i].philo, NULL, ft_philo, &m_s->tab[i]))
		{
			printf("la création du thread numero %d a echouée\n", m_s->tab[i].i);
			return (1);
		}
		i++;
	}
	check_death(m_s);
	return (ft_join(m_s));
}

// Utilise la fontion pthread_join sur tous les threads
int	ft_join(t_struct *ma_structure)
{
	int	i;

	i = 0;
	while (i < ma_structure->info.nb_de_philos)
	{
		if (pthread_join(ma_structure->tab[i].philo, NULL))
		{
			printf("le join numero %d a echoue\n", ma_structure->tab[i].i);
			return (1);
		}
		i++;
	}
	return (0);
}
