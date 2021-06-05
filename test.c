#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

//	pthread_mutex_t	mutex;
int		i = 0;

void	*routine1()
{
	while (i < 1)
		i++;
	return (NULL);
}

void	*routine2()
{
	while (i < 1)
		i++;
	return (NULL);
}

int		multi_thread(void)
{
	pthread_t		p1, p2;

	if (pthread_create(&p1, NULL, &routine1, NULL) != 0)
		return (-1);
	if (pthread_create(&p2, NULL, &routine2, NULL) != 0)
		return (-2);
	if (pthread_join(p1, NULL) != 0)
		return (-3);
	if (pthread_join(p2, NULL) != 0)
		return (-4);
	printf("i : %d\n", i);
	return (0);
}

int main(void)
{
	printf("\nReturn Value = %d\n", multi_thread());
	return (0);
}
