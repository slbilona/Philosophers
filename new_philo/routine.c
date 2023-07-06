#include "philosophers.h"

void	*ft_mort(t_struct *m_s, t_philosophe *actuel)
{
	unsigned long	time;
	pthread_mutex_lock(&m_s->info.mutex_mort);
	m_s->info.i_mort = 0;
	time = ft_time(m_s);
	printf("%ld %d died\n", time, actuel->i);
	return (NULL);
}

int	ft_sleep(t_struct *m_s, t_philosophe *actuel)
{
	if(actuel->time_of_death < ft_time(m_s) || !ft_verif_philos(m_s))
		return (ft_mort(m_s, actuel), 1);
	printf("%ld %d is sleeping\n", ft_time(m_s), actuel->i);
	ft_usleep(m_s->info.tts);
	actuel->sdk = 1;
	return (0);
}

int	ft_think(t_struct *m_s, t_philosophe *actuel)
{
	if(actuel->time_of_death < ft_time(m_s) || !ft_verif_philos(m_s))
		return (ft_mort(m_s, actuel), 1);
	printf("%ld %d is thinking\n", ft_time(m_s), actuel->i);
	ft_usleep(5);
	actuel->sdk = 3;
	return (0);
}

int	ft_verif_philos(t_struct *m_s)
{
	int				i;
	t_philosophe	*actuel;

	i = 0;
	actuel = m_s->philosophe;
	if (m_s->info.i_mort == 0)
		return (0);
	if(m_s->info.notepme != -1)
	{
		while(actuel)
		{
			if (actuel->nb_de_repas < m_s->info.notepme)
				i++;
			actuel = actuel->next;
		}
		if (i > 0)
			return (1);
		return (0);
	}
	return (1);
}