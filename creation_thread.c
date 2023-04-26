/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creation_thread.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilselbon <ilselbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 22:10:30 by ilselbon          #+#    #+#             */
/*   Updated: 2023/04/26 22:12:09 by ilselbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_philo(int *i)
{
	printf("thread philo numero %d\n", *i + 1);
	return (NULL);
}

int	thread_philos(t_struct *jsp)
{
	int				i;
	int				ret;
	t_philosophe	*premier;

	i = 0;
	premier = ft_lstnew(i);
	while (i < jsp->philosophes)
	{
		philo = i;
		ret = pthread_create(&philo, NULL, (void *)ft_philo, &i);
		if (ret != 0)
		{
			printf("la creation du thread numero %d a echouee\n", i);
			return (1);
		}
		ret = pthread_join(philo, NULL);
		if (ret != 0)
		{
			printf("le join numeoro %d a echoue\n", i);
			return (1);
		}
		i++;
	}
	printf("parfait\n");
	return (0);
}
