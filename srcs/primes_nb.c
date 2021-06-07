#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int	primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void	*routine(void *arg)
{
	int	j;

	j = *(int*)arg;
	printf("%d, ", j);
	return (NULL);
}

int		print_all_primes(void)
{
	pthread_t	th[10];

	for (int i = 0; i < 10; i++)
		if (pthread_create(&th[i], NULL, &routine, primes + i) != 0)
			return (-1);
	for (int i = 0; i < 10; i++)
		if (pthread_join(th[i], NULL) != 0)
			return (-1);
	return (0);
}

int		main(void)
{
	if (print_all_primes() < 0)
		printf("Error\n");
	return (0);
}
