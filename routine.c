#include "philosophers.h"

int	ft_mort(t_philosophe *actuel)
{
	unsigned long	time;
	int stop;

	stop = 0;
	if(actuel->time_of_death < ft_time(actuel))
	{
		pthread_mutex_lock(&actuel->info->mutex_mort);
		actuel->info->i_mort = 0;
		stop = 1;
		pthread_mutex_unlock(&actuel->info->mutex_mort);
		pthread_mutex_lock(&actuel->info->m_printf);
		time = ft_time(actuel);
		printf("%ld %d died\n", time, actuel->i);
		pthread_mutex_unlock(&actuel->info->m_printf);
	}
	return (stop);
}

int	ft_sleep(t_philosophe *actuel)
{
	pthread_mutex_lock(&actuel->info->m_printf);
	if(!ft_verif_philos(actuel))
	{
		pthread_mutex_unlock(&actuel->info->m_printf);
		return (1);
	}
	printf("%ld %d is sleeping\n", ft_time(actuel), actuel->i);
	pthread_mutex_unlock(&actuel->info->m_printf);
	ft_usleep(actuel->info->tts, actuel);
	actuel->sdk = 1;
	return (0);
}

int	ft_think(t_philosophe *actuel)
{
	pthread_mutex_lock(&actuel->info->m_printf);
	if(!ft_verif_philos(actuel))
	{
		pthread_mutex_unlock(&actuel->info->m_printf);
		return (1);
	}
	printf("%ld %d is thinking\n", ft_time(actuel), actuel->i);
	pthread_mutex_unlock(&actuel->info->m_printf);
	ft_usleep(5, actuel);
	actuel->sdk = 3;
	return (0);
}

int	ft_verif_philos(t_philosophe *actuel)
{
	int ret;

	ret = 1;
	pthread_mutex_lock(&actuel->info->mutex_mort);
	ret = actuel->info->i_mort;
	pthread_mutex_unlock(&actuel->info->mutex_mort);
	return (ret);
}