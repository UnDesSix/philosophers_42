#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

int	my_usleep(suseconds_t usec)
{
	struct timeval	obj_time;
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	obj_time.tv_usec = current_time.tv_sec * 1E6 + current_time.tv_usec + usec;
	while (current_time.tv_sec * 1E6 + current_time.tv_usec < obj_time.tv_usec)
	{
		gettimeofday(&current_time, NULL);
	}
	return (0);
}

int	main()
{
	struct	timeval prev_time;
	struct	timeval current_time;

	gettimeofday(&current_time, NULL);
	for (int i = 0; i < 10; i++)
	{
		prev_time.tv_usec = current_time.tv_usec;
		my_usleep(90000);
		gettimeofday(&current_time, NULL);
		if (current_time.tv_usec - prev_time.tv_usec > 0)
			printf("%3d : %ld micro seconds\n",
				i, current_time.tv_usec - prev_time.tv_usec);
		else
			printf("%3d : %ld micro seconds\n",
				i, 1000000 + current_time.tv_usec - prev_time.tv_usec);
			
	}
	return (0);
}

