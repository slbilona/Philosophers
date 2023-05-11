#include <pthread.h>
#include <stdio.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *ft_test(void *mutex)
{
	while(1)
	{
		pthread_mutex_lock(mutex);
		printf("1 !\n");
		pthread_mutex_unlock(mutex);
	}
	return (NULL);
}

void *ft_test2(void *mutex)
{
	while(1)
	{
		pthread_mutex_lock(mutex);
		printf("2 !\n");
		pthread_mutex_unlock(mutex);
	}
	return (NULL);
}

void *ft_test3(void *mutex)
{
	while(1)
	{
		pthread_mutex_lock(mutex);
		printf("3 !\n");
		pthread_mutex_unlock(mutex);
	}
	return (NULL);
}

int main()
{
	int ret;
	pthread_t test;
	pthread_t test2;
	pthread_t test3;

	pthread_mutex_init(&mutex, NULL);
	ret = pthread_create(&test, NULL, ft_test, &mutex);
	if(ret)
		return (1);
	ret = pthread_create(&test2, NULL, ft_test2, &mutex);
	if(ret)
		return (1);
	ret = pthread_create(&test3, NULL, ft_test3, &mutex);
	if(ret)
		return (1);
	return (printf("test\n"), 0);
}