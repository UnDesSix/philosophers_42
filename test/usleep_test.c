#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

int	main()
{
	struct	timeval prev_time;
	struct	timeval current_time;

	gettimeofday(&current_time, NULL);
	for (int i = 0; i < 10; i++)
	{
		prev_time.tv_usec = current_time.tv_usec;
		usleep(500);
		gettimeofday(&current_time, NULL);
		printf("%3d : %ld micro seconds\n",
		i, current_time.tv_usec - prev_time.tv_usec);
	}
	return (0);
}
