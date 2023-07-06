/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repas.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 12:36:59 by ilona             #+#    #+#             */
/*   Updated: 2023/07/06 15:05:12 by ilona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//
void	*ft_philo(void *ma_structure)
{
	t_struct		*m_s;
	t_philosophe	*actuel;

	m_s = ma_structure;
	actuel = m_s->philosophe;
	while (actuel->i != m_s->info.index)
		actuel = actuel->next;
	while (ft_verif_philos(m_s))
	{
		actuel->time_of_death = ft_time(m_s) + m_s->info.ttd;
		if (actuel->sdk == 3 && ft_verif_philos(m_s))
		{
			if (ft_eat(m_s, actuel))
				return (NULL);
		}
		if (actuel->sdk == 2 && ft_verif_philos(m_s))
		{
			if (ft_sleep())
				return (NULL);
		}
		if (actuel->sdk == 1 && ft_verif_philos(m_s))
		{
			printf("%ld %d is thinking\n", ft_time(ma_structure), actuel->i);
			ft_usleep(10);
			actuel->sdk = 3;
		}
	}
	return (NULL);
}

// Les philosophes prennent leur fourchettes et mangent
int	ft_eat(t_struct *m_s, t_philosophe *actuel)
{
	if (actuel->i == 1)
		ft_gaucher();
	else
		ft_droitier();
	if(actuel->time_of_death < ft_time(m_s))
	{
		ft_mort();
		return (NULL);
	}
	printf("%ld %d is eating\n", ft_time(ma_structure), actuel->i);
	actuel->nb_de_repas++;
	ft_usleep(m_s->info.tte);
}