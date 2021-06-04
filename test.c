#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

void	*routine(int	*i, MUTEX)
{
	while (*i < 10000000)
	{
		pthread_mutex_lock(MUTEX);
		(*i)++;
		pthread_mutex_unlock(MUTEX);
	}
	return (NULL);
}

int		main(void)
{
	pthread_t	t1;
	pthread_t	t2;
	int 		i;
	
	i = 0;
	pthread_create(&t1, NULL, &routine(&i), NULL);
	pthread_create(&t2, NULL, &routine(&i), NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	printf("i : %d\n", i);
	return (0);
}
