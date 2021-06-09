#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

typedef struct timeval t_timeval;

t_timeval	get_diff(t_timeval prev)
{
	t_timeval current_time;

	gettimeofday(&current_time, NULL);
	printf("diff : %ld seconds and %ld micro seconds\n",
		current_time.tv_sec - prev.tv_sec, current_time.tv_usec - prev.tv_usec);
	return (current_time);
}

int		get_time_laps()
{
	int			i;
	t_timeval	prev;

	i = 0;
	gettimeofday(&prev, NULL);
//while (i++ < 50)
	for (i = 0; i < 50; i++)
		prev = get_diff(prev);
	return (0);
}
/*
int		main()
{
	get_time_laps();
	return (0);
}*/
