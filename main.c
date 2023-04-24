#include "philosophers.h"

//transforme une string en int
int	ft_atoi(const char *nptr)
{
	int	result;
	int	i;
	int	sign;

	sign = 1;
	i = 0;
	result = 0;
	while ((9 <= nptr[i] && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + nptr[i] - 48;
		i++;
	}
	return (result * sign);
}

int main(int ac, char **av)
{
	t_struct jsp;
	if (ac > 6)
		printf("trop d'arguments\n");
	else if (ac < 5)
		printf("pas assez d'arguments\n");
	else if(ac == 6 || ac == 5)
	{
		if(ft_verif_args(ac, av, &jsp))
			printf("erreur : arg\n");
		else
			printf("parfait\n"); 
	}   
	return (0);
}