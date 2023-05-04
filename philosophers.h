/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilselbon <ilselbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 22:13:42 by ilselbon          #+#    #+#             */
/*   Updated: 2023/05/04 22:26:46 by ilselbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

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
	void				*fourchette_g;
	pthread_mutex_t		fourchette_d;
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

int				ft_creation_table(t_struct *jsp);
int				ft_thread_philo(t_philosophe **premier);
int				ft_initialisation(t_philosophe *actuel);
void			*ft_philo(t_philosophe *actuel);

// listes chainees

int				ft_vide_liste(t_philosophe **pile);
t_philosophe	*ft_lstnew(int content);
t_philosophe	*ft_lstadd_back(t_philosophe **lst, t_philosophe *new);

#endif