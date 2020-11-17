/* "[소스 3] thread 예제 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>


void * thread_function(void * arg);


int main()
{
	int result;
	pthread_t thread_index;
	
	void* thread_pointer;
	result = pthread_create(&thread_index, NULL, thread_function, (void*)NULL);
	
	if (result != 0)
	{
		perror("Thread Create Error");
		exit(0);
	}
	
	result = pthread_join(thread_index, &thread_pointer);
	if (result != 0)
	{
		perror("Thread Join Error");
		exit(0);
	}
	printf("Thread Join Return:%s\n", (char*)thread_pointer);
	
	return 0;
}
void * thread_function(void * arg)
{
	printf("Start Thread\n");
	
	sleep(5);
	printf("Call Thread Exit\n");
	pthread_exit("Bye~~");
}
	
