#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>

//Pasing arguments ?!

#define	NB_OF_DICES	8 // 32750 seems to be the maximum nb of threads ont this VM

void	*roll_dice()
{
	int	value;
	int	*res;
	
	value = rand() % 6 + 1;
	res = malloc(sizeof(int));
	*res = value;
	return ((void*)res);
}

int		mult_threading()
{
	pthread_t	thread[NB_OF_DICES];
	int			*res[NB_OF_DICES];
	int			i;

	i = -1;
	while (++i < NB_OF_DICES)
		if (pthread_create(&thread[i], NULL, &roll_dice, NULL))
			return (-1 * (i + 1));
	i = -1;
	while (++i < NB_OF_DICES)
		if (pthread_join(thread[i], (void**)&res[i]))
			return (1 * (i + 1));
	i = -1;
	while (++i < NB_OF_DICES)
		printf("Dice %d : %d\n", i, *res[i]);
	i = -1;
	while (++i < NB_OF_DICES)
		free(res[i]);
	return (0);
}

int		main()
{
	srand(time(NULL));
	printf("Return value : %d\n", mult_threading());
	return (0);
}
