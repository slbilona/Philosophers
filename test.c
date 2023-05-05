#include <pthread.h>
#include <stdio.h>

void *ft_test(void *mutex)
{
	while(1)
	{
		pthread_mutex_lock(mutex);
		printf("hey !\n");
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
	static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

	pthread_mutex_init(&mutex, NULL);
	ret = pthread_create(&test, NULL, ft_test, &mutex);
	if(ret)
		return (1);
	ret = pthread_create(&test2, NULL, ft_test, &mutex);
	if(ret)
		return (1);
	ret = pthread_create(&test3, NULL, ft_test, &mutex);
	if(ret)
		return (1);
	return (0);
}