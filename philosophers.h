/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilselbon <ilselbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 22:13:42 by ilselbon          #+#    #+#             */
/*   Updated: 2023/05/10 21:42:35 by ilselbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_info
{
	int	philosophes;
	int	ttd;
	int	tte;
	int	tts;
	int	notepme;
}	t_info;

typedef struct s_philosophe
{
	int					i;
	int					sdk;
	int					nb_de_repas;
	void				*fourchette_g;
	pthread_t			philo;
	pthread_mutex_t		fourchette_d;
	struct s_philosophe	*next;
}	t_philosophe;

typedef struct s_struct
{
	int					index;
	struct s_info 		info;
	struct s_philosophe *philosophe;
}	t_struct;


// main

int				ft_atoi(const char *nptr);

// checker

int				ft_isdigit(int c);
int				ft_chiffres(char **av, int j, int i);
int				ft_verif_args(int ac, char **av, t_info *jsp);

// creation_thread

int				ft_creation_table(t_struct *jsp);
int				ft_thread_philo(t_struct *jsp);
int				ft_initialisation(t_philosophe *actuel);
void			*ft_philo(void *actuel);

// listes chainees

int				ft_vide_liste(t_philosophe **pile);
t_philosophe	*ft_lstnew(int content);
t_philosophe	*ft_lstadd_back(t_philosophe **lst, t_philosophe *new);

#endif