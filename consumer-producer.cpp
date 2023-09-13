#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#include<stdlib.h>
#include<iostream>
using namespace std ;


sem_t s,e,f ;

int in = 0 , out = 0 ;

int bufferSize = 5 ;

int buffer[5];

void* producer(void* arg)
{
	sem_wait(&e);
		sem_wait(&s);
			buffer[in] = 1 + (rand() % 100) ;
			in = (in+1)%bufferSize ;
			cout<<in<<" Im in producer "<<buffer[in-1] <<"\n" ;
		sem_post(&s);
	sem_post(&f);
	
	sleep(1);
	
}

void* consumer(void* arg)
{
	int val = 0;
	int data = 0;

	
	do{
		sem_wait(&f);
			sem_wait(&s);
				data = buffer[out] ;
				out = (out+1)%bufferSize ; 
				cout<<out<<" Im in consumer "<<data<<"\n";
			sem_post(&s);
		sem_post(&e);
		sem_getvalue(&e,&val) ;
	}while(val != 5);
	
	sleep(1);
}

int main()
{
	sem_init(&s,0,1);
	sem_init(&e,0,5);
	sem_init(&f,0,0);
	
	pthread_t tidp[5],tidc ;
	
	pthread_create(&tidc,NULL,consumer,NULL) ;
	
	for(int i = 0 ; i < 3 ; i++)
	{
		pthread_create(&tidp[i],NULL,producer,NULL) ;
	}
	
	return 0 ;
}
