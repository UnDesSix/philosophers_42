#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

int		main()
{
	int i;

	i = 0;
	while (i++ < 20)
		sleep(1);
	return (0);
}
