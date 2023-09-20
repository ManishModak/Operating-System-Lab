#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#include<stdio.h>

sem_t writer , reader ;

int readerCount = 0 ;

void* writerFunction(void* arg) {

		
	sem_wait(&writer) ;
		printf("Thread %ld is writing\n",pthread_self());
	sem_post(&writer) ;
	
	sleep(1);
}

void* readerFunction(void* arg) {
	
	
	sem_wait(&reader);
		readerCount++;
		if(readerCount == 1)
			sem_wait(&writer);
	sem_post(&reader);
	
		printf("Thread %ld is reading\n",pthread_self());
		
	sem_wait(&reader);
		readerCount--;
		if(readerCount == 0)
			sem_post(&writer);
	sem_post(&reader);
	
	sleep(1);
}

int main() {

	sem_init(&writer,0,1);
	sem_init(&reader,0,1);
	
	pthread_t tidwriter[3],tidreader[3] ;
	
	pthread_create(&tidwriter[0],NULL,writerFunction,NULL);
	pthread_create(&tidreader[0],NULL,readerFunction,NULL);
	pthread_create(&tidreader[1],NULL,readerFunction,NULL);
	pthread_create(&tidwriter[1],NULL,writerFunction,NULL);
	pthread_create(&tidreader[2],NULL,readerFunction,NULL);
	pthread_create(&tidwriter[2],NULL,writerFunction,NULL);
	
	sleep(5);
	
	return 0 ;
}

---------------------------------------------------------------------------------------------------------------------
student@student:~$ gcc reader-writer.c
student@student:~$ ./a.out

Thread 139758644753984 is writing
Thread 139758636361280 is reading
Thread 139758627968576 is reading
Thread 139758476965440 is reading
Thread 139758611183168 is writing
Thread 139758619575872 is writing
