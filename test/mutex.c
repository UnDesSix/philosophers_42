#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>


int		mutex_test()
{
	pthread_mutex_t	test;
	int				res0;
	int				res1;

	pthread_mutex_init(&test, NULL);
//	pthread_mutex_lock(&test);
	res0 = pthread_mutex_unlock(&test);
	res1 =pthread_mutex_destroy(&test);
	printf("res 0: %d\n", res0);
	printf("res 1: %d\n", res1);
	return (0);
}

int		main()
{
	mutex_test();
	return (0);
}
