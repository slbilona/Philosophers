#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>

typedef struct s_struct{
    int philosophes;
    int ttd;
    int tte;
    int tts;
    int notepme;
}   t_struct;

// main

int ft_atoi(const char *nptr);

// checker

int	ft_isdigit(int c);
int	ft_chiffres(char **av, int j, int i);
int ft_verif_args(int ac, char **av, t_struct *jsp);


#endif