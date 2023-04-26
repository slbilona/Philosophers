/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilselbon <ilselbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 22:13:42 by ilselbon          #+#    #+#             */
/*   Updated: 2023/04/26 22:30:47 by ilselbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_struct
{
	int	philosophes;
	int	ttd;
	int	tte;
	int	tts;
	int	notepme;
}	t_struct;

typedef struct s_philosophe
{
	int					i;
	int					*fourchette_g;
	int					fourchette_d;
	int					nb_de_repas;
	pthread_t			philo;
	struct s_philosophe	*next;
}	t_philosophe;

// main

int				ft_atoi(const char *nptr);

// checker

int				ft_isdigit(int c);
int				ft_chiffres(char **av, int j, int i);
int				ft_verif_args(int ac, char **av, t_struct *jsp);

// creation_thread

int				thread_philos();
void			*ft_philo(int *i);

// listes chainees

void			ft_vide_liste(t_philosophe **pile);
t_philosophe	*ft_lstnew(int content);
t_philosophe	*ft_lstadd_back(t_philosophe **lst, t_philosophe *new);

#endif