#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

void	*routine1(void *tom)
{
	int i = 0;
//	while (i < 10000000)
//		i++;
	printf("Hello routine 1\n");
	return (NULL);
}

void	*routine2(void *matt )
{
	printf("Hello routine 2\n");
	return (NULL);
}


int		main(void)
{
	pthread_t	t1;
	pthread_t	t2;

	pthread_create(&t1, NULL, &routine1, NULL);
	pthread_create(&t2, NULL, &routine2, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	return (0);
}
