/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 12:36:38 by ilona             #+#    #+#             */
/*   Updated: 2023/07/06 21:00:22 by ilona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_info
{
	int					ttd;
	int					tte;
	int					tts;
	int					index;
	int					i_mort;
	int					notepme;
	int					nb_de_philos;
	struct timeval		debut;
	pthread_mutex_t		mutex_mort;
}	t_info;

typedef struct s_philosophes
{
	int						i;
	int						vie;
	int						sdk;
	int						nb_de_repas;
	void					*fourchette_g;
	unsigned long			time_of_death;
	pthread_t				philo;
	pthread_mutex_t			fourchette_d;
	struct s_philosophes	*next;
}	t_philosophe;

typedef struct s_struct
{
	struct s_info			info;
	struct s_philosophes	*actuel;
	struct s_philosophes	*philosophe;
}	t_struct;

// Checkers

int				ft_isdigit(int c);
int				ft_chiffres(char **av, int j, int i);
int				ft_verif_args(int ac, char **av, t_info *ma_structure);

// Creation thread

int				ft_join(t_struct *ma_structure);
int				ft_creation_table(t_struct *ma_structure);
int				ft_lancement_thread(t_struct *ma_structure);

// Listes Chainees

void			ft_vide_liste(t_struct *m_s);
t_philosophe	*ft_lstnew(int i);
t_philosophe	*ft_lstadd_back(t_philosophe **lst, t_philosophe *new);

// Utils

int				ft_atoi(const char *nptr);
void			ft_usleep(int tmp);
unsigned long	ft_time2(struct timeval debut);
unsigned long	ft_time(t_struct *ma_structure);

//	Repas

int				ft_eat(t_struct *m_s, t_philosophe *actuel);
int				ft_gauchers(t_struct *m_s, t_philosophe *actuel);
int				ft_droitiers(t_struct *m_s, t_philosophe *actuel);
void			*ft_philo(void *ma_structure);
void			ft_lache_fourchette(t_philosophe *actuel);


// Routine

int				ft_think(t_struct *m_s, t_philosophe *actuel);
int				ft_sleep(t_struct *m_s, t_philosophe *actuel);
int				ft_verif_philos(t_struct *m_s);
void			*ft_mort(t_struct *m_s, t_philosophe *actuel);


#endif