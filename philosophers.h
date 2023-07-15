/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 12:36:38 by ilona             #+#    #+#             */
/*   Updated: 2023/07/15 18:21:30 by ilona            ###   ########.fr       */
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
	int						ttd;
	int						tte;
	int						tts;
	int						ate;
	int						index;
	int						i_mort;
	int						notepme;
	int						nb_de_philos;
	struct timeval			debut;
	pthread_mutex_t			m_ate;
	pthread_mutex_t			m_printf;
	pthread_mutex_t			mutex_mort;
	pthread_mutex_t			m_stop;
	struct s_philosophes	**actuel_philo;
}	t_info;

typedef struct s_philosophes
{
	int						i;
	int						vie;
	int						sdk;
	int						ate;
	int						nb_de_repas;
	void					*fourchette_g;
	long int				time_of_death;
	pthread_t				philo;
	struct s_info			*info;
	pthread_mutex_t			m_tod;
	pthread_mutex_t			mutex;
	pthread_mutex_t			fourchette_d;
}	t_philosophe;

typedef struct s_struct
{
	struct s_info			info;
	struct s_philosophes	*tab;
}	t_struct;

// Checkers

int				ft_isdigit(int c);
int				ft_chiffres(char **av, int j, int i);
int				ft_verif_args(int ac, char **av, t_info *ma_structure);
void			ft_init_info(char **av, t_info *info);

// Creation thread

int				ft_join(t_struct *ma_structure);
int				ft_creation_table(t_struct *ma_structure);
int				ft_lancement_thread(t_struct *ma_structure);
void			ft_init_tab(t_struct *ma_structure);

// Utils

int				ft_atoi(const char *nptr);
int				ft_print(t_philosophe *actuel, char *str, int eat_or_not);
void			ft_destroy(t_struct *m_s);
void			ft_usleep(int tmp, t_philosophe *philo);
long int		ft_time(t_philosophe *philo);
long int		ft_time2(struct timeval debut);

//	Repas

int				ft_eat(t_philosophe *actuel);
void			*ft_philo(void *philo);
void			ft_lache_fourchette(t_philosophe *actuel);

// Routine

int				ft_sleep(t_philosophe *actuel);
int				ft_gauchers(t_philosophe *actuel);
int				ft_droitiers(t_philosophe *actuel);

// Verif Mort

int				ft_mort(t_philosophe *actuel);
int				ft_verif_philos(t_philosophe *actuel);
void			check_death(t_struct *ma_structure);

#endif